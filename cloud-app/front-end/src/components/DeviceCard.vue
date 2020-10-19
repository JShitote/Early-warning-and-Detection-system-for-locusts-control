<template>
  <div id="devicecard">
    <b-card>
      <b-row>
        <b-col>
          <b-card-text class="mb-2">{{ device_id }}</b-card-text>
        </b-col>
        <b-col align="right">
          <b-icon icon="x-circle" @click="closeCard"> </b-icon>
        </b-col>
      </b-row>
      <b-tabs content-class="mt-3" active-nav-item-class="p-2 bg-white text-primary border-bottom border-warning rounded-0 "  pills medium lazy>
        <b-tab title="Metrics" active>
          <Metrics :graphData="[]" :deviceData="deviceData"></Metrics>
        </b-tab>
        <b-tab title="Trend">
          <HighCharts
            :sensorData="sensorData"
            :device_id="device_id"
          ></HighCharts>
        </b-tab>
      </b-tabs>
    </b-card>
  </div>
</template>

<script>
import axios from 'axios'
import { bus } from '../main'
import Metrics from '@/components/Metrics.vue'
import HighCharts from '@/components/HighCharts.vue'

export default {
  components: {
    Metrics,
    HighCharts
  },
  props: {
    device_id: {
      required: true
    }
  },
  data() {
    return {
      deviceData: null,
      dev_id: null,
      sensorData: []
    }
  },
  methods: {
    closeCard: function() {
      bus.$emit('showCard', { show: false })
    },
    async fetchDeviceData(device_id = 'Orange1') {
      let { data } = await axios.get(
        `https://api.waziup.io/api/v2/devices/${device_id}`
      )
      this.sensorData = [] //ensures that array is empty before any api call
      return Object.values(data.sensors).map(item => {
        let {
          name,
          value: { timestamp, value },
          id
        } = item

        this.sensorData.push(id)
        return {
          name,
          id,
          timestamp,
          value
        }
      })
    }
  },
  watch: {
    async device_id(newVal) {
      this.deviceData = await this.fetchDeviceData(newVal)
    }
  },
  async mounted() {
    this.deviceData = await this.fetchDeviceData()
  }
}
</script>

<style scoped>
#devicecard {
  width: 501px;
  height: 509px;
  /* border: 1px solid red */
  margin-left: auto;
}
.card-text {
  font-size: 21.034px;
  font-style: normal;
  text-align: left;
}

.border-bottom{

  border-bottom: 2px solid crimson

}
/* .nav-link{
  padding: 0.2rem 0.5rem
}
.nav-pills .nav-link {
    border-radius: 0.05rem;
    border-bottom: 5px solid red;
}
.nav-pills .nav-link.active, .nav-pills .show > .nav-link {
    color: #000; 
    border-bottom: 2px solid#007bff;
    /* background-color: #007bff; 
} */
</style>
