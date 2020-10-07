const mongoose = require("mongoose");

const Schema = mongoose.Schema;

const deviceSchema = new Schema({
  name: {
    type: String,
    maxlength: 50
  },
  dev_id: {
    type: String,
    required: true,
    maxlength: 100
  },
  app_id: {
    type: String,
    required: true,
    maxlength: 100
  },
  location: {
    type: String
  },
  parameters: [String],
  units: {},
  lat: String,
  lon: String,
  description: String,
  created_by: {
    type: Schema.Types.ObjectId,
    ref: "user"
  },
  last_seen: Date
});

module.exports = mongoose.model("device", deviceSchema);
