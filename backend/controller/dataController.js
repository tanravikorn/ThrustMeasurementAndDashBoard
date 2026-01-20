import db from '../database/db.js'


/** @type {import("express").RequestHandler} */
export const getData = async (req, res) => {
    const limit = req.query.limit || 100;

    const sql = `SELECT * FROM data ORDER BY id DESC LIMIT ?`;

    db.all(sql, [limit], (err, rows) => {
        if (err) {
            console.error(err.message);
            return res.status(500).json({ error: err.message });
        }

        return res.status(200).json(rows);
    });
};

/** @type {import("express").RequestHandler} */
export const postData = async (req, res) => {
    const {thrust, voltage, current, power} = req.body;

    const sql  = `INSERT INTO data(thrust, voltage, current, power) VALUES (?,?,?,?)`;

    db.run(sql, [thrust, voltage, current, power], function(err) {
        if(err){
            console.error(err.message);
            return res.status(500).send(JSON.stringify({error : err.message}));
        }

        console.log("Insert success");

        const io = req.app.get('socketio');

        const newRecord = {
            id: this.lastID,
            thrust,
            voltage,
            current,
            power,
            timestamp: new Date().toISOString() // ส่งเวลาปัจจุบันไปด้วย
        };
        io.emit("new-sensor-data", newRecord);

        return res.status(200).send(JSON.stringify({
            message : "success",
            id : this.lastID
        }));
    });
}


/** @type {import("express").RequestHandler} */
export const clearData = async (req,res) => {
    try{
        db.serialize(() => {
        db.run("DELETE FROM data");
        db.run("DELETE FROM sqlite_sequence WHERE name='data'");
        });
        const io = req.app.get('socketio');
        if(io) io.emit("clear-data");
        return res.status(200).send(JSON.stringify({message : "Succces clear "}));
    }catch (err){
        return res.status(500).send(JSON.stringify({message : "can not clear"}));
    }
}

/** @type {import("express").RequestHandler} */
export const exportData = async (req, res) => {
    const sql = `SELECT * FROM data ORDER BY id ASC`;

    db.all(sql, [], (err, rows) => {
        if (err) {
            console.error(err.message);
            return res.status(500).send("Error retrieving data");
        }
        let csvContent = "id,timestamp,thrust,voltage,current,power\n";

        rows.forEach((row) => {
            const cleanTime = new Date(row.timestamp).toLocaleString();
            csvContent += `${row.id},"${cleanTime}",${row.thrust},${row.voltage},${row.current},${row.power},${row.rpm}\n`;
        });

        const fileName = `motor_test_${Date.now()}.csv`;

        res.header('Content-Type', 'text/csv');
        res.header('Content-Disposition', `attachment; filename="${fileName}"`);
        
        return res.status(200).send(csvContent);
    });
};


