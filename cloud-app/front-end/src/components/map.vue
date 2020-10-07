<template>
  <div style="width:100vw;height:100vh;position:relative">
 
 <l-map
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
 <l-marker :lat-lng="markerLatLng" @click="innerClick"></l-marker>
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
      markerLatLng:[48.1456,-1.24553],
      deviceid: null
  } 
  },
  methods:{
     zoomUpdate(zoom) {
      this.currentZoom = zoom;
    },
    centerUpdate(center) {
      this.currentCenter = center;
    },
    innerClick() {
      bus.$emit('showCard',{
        id: this.deviceid,
        show: true
      })
     
    }

  },
  computed:{

   
  },
  mounted(){
    // this.centerUpdate(this.markerLatLng);
    this.showMap = true

    bus.$on('marker', data =>{
      this.markerLatLng = data.location;
      this.devideid = data.id;
    })

    
    
  }
  



}
</script>

<style>



</style>