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
    
    <Metrics  :data ="devicedata" ></Metrics>
    
    </b-tab>
    <b-tab title="trend"><p>I'm the second tab</p></b-tab>
  </b-tabs>
  </b-card>
  
  </div>
</template>

<script>
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
mounted(){


   var db = firebase.database().ref();

    db.on('value',(snap)=>{

      let {livedata} = snap.val();

      this.deviceData = livedata.data

    })

   
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