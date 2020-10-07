<template>
  <div id="devicecard">
  <b-card>
  <b-row >
    <b-col>
    
    <b-card-text>Langata hospital</b-card-text>
    </b-col>
    <b-col align="right">
    
    <b-icon icon="x-circle" @click="closeCard"> </b-icon>
    </b-col>
  
  </b-row>
    <b-tabs content-class="mt-3">
    <b-tab title="metrics" active>
    
    <Metrics :graphData="[]"  :deviceData ="deviceData" ></Metrics>
    
    </b-tab>
    <b-tab title="trend"><p>I'm the second tab</p></b-tab>
  </b-tabs>
  </b-card>
  
  </div>
</template>

<script>
import axios from 'axios';
import {bus} from '../main';
import Metrics from "@/components/Metrics.vue";
import firebase from '../firebase'


export default {

components:{
  Metrics
},
props:{
  devicedata:{
    type:Object
  },
  device_id:{
    required:true
  }
},
data(){
  return {
    windDrirection:{
      name:'DIR',
      value: null
    },
    humidity:{
      name:'HUM',
      value: null
    },
    temperature:{
      name:'TC',
      value: null
    },
    windSpeed:{
      name:'SPD',
      value: null
    },
    deviceData: null
  }
},
methods:{
    closeCard:function(){
         bus.$emit('showCard', { show:false  })
             }
},
async mounted(){

 let { data , status} = await axios.get('https://api.waziup.io/api/v2/devices/Orange1');

 console.log(typeof data.sensors, 'status', status)

let sensorData =  Object.values(data.sensors).map(item=>{

   let { name , value:{timestamp, value }, id} = item
   return {
    name,
    id,
    timestamp,
    value
   }

 })


this.deviceData = sensorData;

 console.log(this.deviceData)


  
   
}
  

}
</script>

<style scoped>

#devicecard {
width: 501px;
height: 509px;
/* border: 1px solid red */
margin-left:20px;

}
.card-text {
  font-size:21.034px;
  font-style: normal;
  text-align: left;
}

</style>