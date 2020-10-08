const functions = require('firebase-functions');
const cors = require('cors');
const express = require('express');
const bodyParser = require('body-parser');


const app = express();

app.use(cors({
  origin: true
}));
app.use(bodyParser.json());

app.get('/',(req,res)=>{
  res.send({hello:"hello"})
})


// Testing express endpoints
exports.app = app;

// Firebase endpoint
exports.api = functions.https.onRequest(app);

