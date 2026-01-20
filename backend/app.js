import express from "express";
import cors from "cors";
import { createServer } from 'http';
import {Server} from "socket.io"
import dataRoute from "./route/dataRoute.js";
import db from "./database/db.js";
import socketHandle from "./socket/socketHandle.js";
const app = express();
const port  = 3000;

const httpServer = createServer(app);
const io = new Server(httpServer, {
    cors:{
        origin: "*",
        methods: ["GET", "POST"]
    }
})

app.use(cors());
app.use(express.json());

app.set('socketio', io);

app.use("/api/data", dataRoute);

httpServer.listen(port, "0.0.0.0", () => {
    console.log(`Backend Server ready at http://localhost:${port}`);
});

socketHandle(io);