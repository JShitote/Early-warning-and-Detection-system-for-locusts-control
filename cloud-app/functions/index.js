const functions = require('firebase-functions');
const cors = require('cors');
const express = require('express');
const bodyParser = require('body-parser');
const mongoose =  require('mongoose');


const config = functions.config()
const app = express();

mongoose.connect(config.env.mongo_url, {
  useNewUrlParser: true,
  useCreateIndex: true,
  useFindAndModify: false,
  useUnifiedTopology: true
});


mongoose.connection.on('connection', error => console.log(error));
const db = mongoose.connection;
db.once('open', () => {
  console.log('Db connected')
});
mongoose.Promise = global.Promise;


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

