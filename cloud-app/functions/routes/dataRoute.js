const express = require("express");
const {
  createData
  
} = require("../controllers/dataController");

const router = express.Router();

//store telemetry
router.post("/create", createData);

// get all telemetry
router.get("/getdata/:dev_id", getAllData);
