import db from "../database/db.js";

export default function(io) {
    io.on("connection", (socket) => {
        socket.on("get-history", (callback) => {
        db.all("SELECT * FROM data ORDER BY id ASC", [], (err, rows) => {
            if (err) {
                callback({ status: "error", message: err.message });
            } else {
                callback({ status: "ok", data: rows });
            }
        });
        });

        //for control esp32 from botton
        socket.on("control-command", (status) => {
            console.log("Command received:", status);
            io.emit("esp32-control", status);
        });
        //esc control
        socket.on("control-throttle", (value) => {
        // value ควรเป็น 0-4095
            io.emit("esp32-throttle", value);
        });

        //record data
        socket.on("esp32-send-data", (data) => {
            let parsedData = (typeof data === 'string') ? JSON.parse(data) : data;
            const { thrust, voltage, current, power , rpm} = parsedData;
            const sql = `INSERT INTO data(thrust, voltage, current, power, rpm) VALUES (?,?,?,?)`;

            db.run(sql, [thrust, voltage, current, power,rpm], function(err) {
                if (err) return console.error(err.message);
                const newRecord = {
                    id: this.lastID,
                    thrust, 
                    voltage, 
                    current, 
                    power,
                    rpm,
                    timestamp: new Date().toISOString()
                };
                //push to frontend 
                io.emit("new-sensor-data", newRecord);
            });
        });

        socket.on("disconnect", () => {
            console.log("Client Disconnected:", socket.id);
        });
    });
}