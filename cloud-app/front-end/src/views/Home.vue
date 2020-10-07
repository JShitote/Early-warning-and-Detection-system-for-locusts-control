<template>
  <div class="main">
    <div class="map">
      <Map :devices="deviceData"></Map>
    </div>
    <div class="search">
      <Search></Search>
    </div>
    <div class="deviceCard">
      <DeviceCard v-show="isCardVisible" :device_id="device_id"></DeviceCard>
    </div>
  </div>
</template>

<script>
import { bus } from '../main'

import Search from '@/components/SearchBar.vue'
import DeviceCard from '@/components/DeviceCard.vue'
import Map from '@/components/map.vue'
import axios from 'axios'

export default {
  name: 'Home',
  components: {
    Search,
    DeviceCard,
    Map
  },
  data() {
    return {
      markerLatLng: [],
      deviceData: {},
      isCardVisible: false,
      device_id: ''
    }
  },
  async created() {
    let { data, status } = await axios.get(
      'https://api.waziup.io/api/v2/devices?q=owner==marvin.johnson@orange.com'
    )

    this.deviceData = data

    bus.$on('showCard', snap => {
      this.device_id = snap.id
      this.isCardVisible = snap.show
    })
  }
}
</script>

<style>
.main {
  position: relative;
  top: 0px;
  bottom: 0px;
  z-index: 0;
  height: 100vh;
  width: 100vw;
}

.map {
  position: absolute;
  top: 0px;
  left: 0px;
  z-index: 2;
}
.search {
  position: relative;
  top: 0px;
  left: 0px;
  z-index: 3;
}
.deviceCard {
  position: absolute;
  top: ;
  left: 60%;
  z-index: 5;
}
</style>
