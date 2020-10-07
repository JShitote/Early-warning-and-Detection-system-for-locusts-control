<template>
<div id="card-data">
<b-container>
  

  
<template v-for="(group,i) in chunkedData" >

  <b-row :key='i' >
    <b-col  class="card-data" v-for="(item,i) in group" :key="i">
        <div>
            <b-icon icon="search"> </b-icon>
        </div>
        <div class='card-text'>
        {{item.name | replaceWord }}   
        </div>
        <div class="card-text-data">
          {{item.value}}
        </div>
    </b-col>
    </b-row>
  </template>
  
</b-container>

</div>
</template>

<script>
import {bus} from '../main';
import {chunk} from 'lodash';

export default {
  props:{
    devicedata:{
      
    }
  },
  data(){
      return{
        data:[{
          name: "DIR",
          value: 182  
        },
        {
          name: "HUM",
          value: 12  
        },
        {
          name: "SPD",
          value: 30  
        },
        {
          name: "TC",
          value: 30  
        }],
        itemPerRow:3
      } 
      
      },
      computed:{
          chunkedData: function(){
              return chunk(this.data,2)
          }
      },
      filters:{
        replaceWord: function(value){
            if(!value) return ''
            switch(value){
                case 'HUM':
                    return 'Humidity'
                case 'SPD':
                    return 'Wind Speed'
                case 'TC' :
                    return 'Temperature'
                case 'DIR':
                    return 'Wind Direction'
            }

        }
      },    
      mounted(){

     bus.$on('marker', snap =>{

       
      this.data = snap.data

      
    })

  }


}
</script>

<style  scoped>
.card-data {
  border:1px solid hsl(220, 9%, 87%);
  border-radius: 8px;
  padding:10px;
  width: 10px;
  margin:15px;
  height:117px;
}
.card-text {
  margin-top:5px;
  padding:5px;
  text-align:center;
  font-size: 13px;
}
.card-text-data {
  padding:5px;
  text-align:center;
  font-size: 13px;
}

</style>