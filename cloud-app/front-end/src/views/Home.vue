<template>
  <div class = "main">


  <div class="map">
         <Map ></Map>
  </div>
  <div class="search">
<Search></Search>
  </div>
  <div class="deviceCard">
   <DeviceCard v-show="isCardVisible" :device-data="devicedata"></DeviceCard>
  </div>


    
    
   
  </div>
</template>

<script>
import firebase from '../firebase'
import {bus} from '../main';

import Search from "@/components/SearchBar.vue";
import DeviceCard from "@/components/DeviceCard.vue";
import Map from "@/components/map.vue";
import axios from 'axios'

export default {
  name: "Home",
  components: {
    Search,
    DeviceCard,
    Map
  },
  data(){

    return {
      markerLatLng : [],
      devicedata : {},
      isCardVisible: false
    }

  },
  async created(){

   let { data, status} = await axios.get('https://api.waziup.io/api/v2/devices?q=owner==marvin.johnson@orange.com')
   console.log(data);

   this.devicedata = data;




    var db = firebase.database().ref();


    db.once('value')
      .then(snapshot =>{
        let { data } = snapshot.val();

        bus.$emit('marker', {
        location:data.latLng,
        id:data.id,
        
      })
      })

    db.on('value',(snap)=>{



      let {livedata} = snap.val();

      bus.$emit('marker', {
        location:livedata.latLng,
        id:livedata.id,
        data: livedata.data,
        time: livedata.date_modified
      })



    })

    bus.$on('showCard', snap =>{
        this.isCardVisible = snap.show
    })
  }
};
</script>

<style >

.main {

position:relative;
top:0px;
bottom:0px;
 z-index:0;
 height: 100vh;
 width:100vw;

}

.map  {
  position: absolute;
  top:0px;
  left:0px;
  z-index:2;

 }
.search{
  position: relative;
  top:0px;
  left:0px;
z-index:3;
}
.deviceCard{
  position: absolute;
  top:;
  left:60%;
  z-index:5;

}

</style>
