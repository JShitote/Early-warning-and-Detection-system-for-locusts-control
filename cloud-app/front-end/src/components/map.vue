<template>
  <div  id="map">
  <code style="margin-top:300px;">
  </code>
 
 <l-map
 ref="map"
 :zoom='zoom'
 v-if="showMap"
 :center="center"
 :options="mapOptions" 
  @update:center="centerUpdate"
  @update:zoom="zoomUpdate"
 >
 <l-tile
  :url="url"
  :attribution="attribution"
 ></l-tile>

 <template v-for="item in deviceLocation">
 <l-marker :lat-lng="[item.location.latitude,item.location.longitude]" @click="showMarkerCard(item.id)" :key="item.id"></l-marker>
 
 </template>
 <l-control-zoom position="bottomright"></l-control-zoom>
 </l-map>

  </div>
</template>


<script>
import {bus} from '../main';
import{ latLng, Icon} from 'leaflet';
import { LMap, LTileLayer, LControlZoom, LMarker } from "vue2-leaflet";

delete Icon.Default.prototype._getIconUrl;
Icon.Default.mergeOptions({
  iconRetinaUrl: require('leaflet/dist/images/marker-icon-2x.png'),
  iconUrl: require('leaflet/dist/images/marker-icon.png'),
  shadowUrl: require('leaflet/dist/images/marker-shadow.png'),
});

export default {
  props:{

    devices:{
      required:true
    }

  },
  components:{
    LMap,
    "l-tile": LTileLayer,
    LControlZoom,
    LMarker
    
  },
  data(){
    
       return {
          zoom: 7,
          center: latLng(47.41322, -1.219482),
          url: 'https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',
          attribution:
            '&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors',
          withPopup: latLng(47.41322, -1.219482),
          withTooltip: latLng(47.41422, -1.250482),
          currentZoom: 5,
          currentCenter: latLng(48.41322, -1.219482),
          showParagraph: false,
          mapOptions: {
            zoomSnap: 0.5,
            zoomControl: false
          },
          showMap: false,
  } 
  },
  methods:{
     zoomUpdate(zoom) {
      this.currentZoom = zoom;
    },
    centerUpdate(center) {
      this.currentCenter = center;
    },
    showMarkerCard(id) {

      bus.$emit('showCard',{
        id,
        show: true
      })
     
    },

  },
  computed:{


    deviceLocation(){

      return Object.values(this.devices).map((element,i)=>{

        let { id ,gateway_id,location, name } = element;
       
          return {
           id,
           gateway_id,
           location,
           name
          }

      })

    }

   
  },
  mounted(){
     this.showMap = true

  }
  



}
</script>

<style>
#map {
  width:100vw;
  height:100vh;
  position:relative;
}


</style>