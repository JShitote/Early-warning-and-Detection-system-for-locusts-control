<template>
  <div id="devicecard">
    <b-card>
      <b-row>
        <b-col>
          <b-card-text>Langata hospital</b-card-text>
        </b-col>
        <b-col align="right">
          <b-icon icon="x-circle" @click="closeCard"> </b-icon>
        </b-col>
      </b-row>
      <b-tabs content-class="mt-3" lazy>
        <b-tab title="metrics" active>
          <Metrics :graphData="[]" :deviceData="deviceData"></Metrics>
        </b-tab>
        <b-tab title="trend">
          <HighCharts :chart="[]"></HighCharts>
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
      windDrirection: {
        name: 'DIR',
        value: null
      },
      humidity: {
        name: 'HUM',
        value: null
      },
      temperature: {
        name: 'TC',
        value: null
      },
      windSpeed: {
        name: 'SPD',
        value: null
      },
      deviceData: null,
      dev_id: null
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

      return Object.values(data.sensors).map(item => {
        let {
          name,
          value: { timestamp, value },
          id
        } = item
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
</style>
