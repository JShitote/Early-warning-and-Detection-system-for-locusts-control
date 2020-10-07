const mongoose = require('mongoose');


const schema = mongoose.Schema; 
const deviceSchema = new schema(
  {
   
  },
  {
    timestamps: {
      createdAt: 'createdAt',
      updatedAt: 'updatedAt'
    }
  }
);
