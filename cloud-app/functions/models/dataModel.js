const mongoose = require("mongoose");

const Schema = mongoose.Schema;

const dataSchema = new Schema(
  {
    time: Date,   
    dev_id: {
      type: String,
      required: true
    },
    app_id: {
      type: String,
      required: true
    }
  },
  { strict: false }
);

module.exports = mongoose.model("telemetry", dataSchema);
