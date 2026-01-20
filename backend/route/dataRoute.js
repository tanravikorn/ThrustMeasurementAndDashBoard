import express from 'express';
import * as dataController from "../controller/dataController.js";


const router = express.Router();

router.post("/", dataController.postData);
router.get("/", dataController.getData);
router.delete("/clear", dataController.clearData);
router.get("/export", dataController.exportData);
export default router;
