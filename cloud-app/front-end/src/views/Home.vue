<template>
  <div class="home">
    <Search></Search>
    <DeviceCard></DeviceCard>
    <Map></Map>
  </div>
</template>

<script>
import Search from "@/components/SearchBar.vue";
import DeviceCard from "@/components/DeviceCard.vue";
import Map from "@/components/map.vue";

export default {
  name: "Home",
  components: {
    Search,
    DeviceCard,
    Map
  }
};
</script>
