import sqlite3 from 'sqlite3';
const sqlite = sqlite3.verbose();
let sql;
//connect to db
const db = new sqlite.Database('./database/data.db', sqlite.OPEN_READWRITE | sqlite.OPEN_CREATE , (err) => {
    if (err) console.error(err.message);
    else {
        console.log("Connected to SQLite");
        db.run("PRAGMA journal_mode = WAL");
    }
});

//Create Table
sql = `CREATE TABLE IF NOT EXISTS data(id INTEGER PRIMARY KEY AUTOINCREMENT, thrust REAL, voltage REAL,
         current REAL, power REAL, rpm INTEGER ,timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)`;

db.run(sql, (err) => {
    if(err) console.log("error creating table");
    else console.log("Created success");
});

export default db;