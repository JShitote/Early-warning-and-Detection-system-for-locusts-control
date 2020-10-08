<template>
  <div id="card-data">

    <template v-if="!Array.isArray(deviceData) || !deviceData.length">

    <p>Oooops!! Seem there is no data at this place</p>
    </template>
    <b-container v-else>
      <template v-for="(group, i) in chunkedData">
        <b-row :key="i">
          <b-col class="card-data" v-for="(item, i) in group" :key="i">
            <div>
              <b-icon icon="search"> </b-icon>
            </div>
            <div class="card-text">
              {{ item.name | replaceWord }}
            </div>
            <div class="card-text-data">
              {{ item.value }}
            </div>
          </b-col>
        </b-row>
      </template>
    </b-container>
  </div>
</template>

<script>
import { chunk } from 'lodash'

export default {
  props: {
    deviceData: {
      required: true
    }
  },
  computed: {
    chunkedData: function() {
      return chunk(this.deviceData, 2)
    }
  },
  filters: {
    replaceWord: function(value) {
      if (!value) return ''
      switch (value) {
        case 'HUM':
          return 'Humidity'
        case 'sHm':
          return 'Soil Humidity'
        case 'PH':
          return 'Soil pH'
        case 'RD':
          return 'Rain Drop'
        case 'SPD':
          return 'Wind Speed'
        case 'TC':
          return 'Temperature'
        case 'DIR':
          return 'Wind Direction'
      }
    }
  }
}
</script>

<style scoped>
.card-data {
  border: 1px solid hsl(220, 9%, 87%);
  border-radius: 8px;
  padding: 10px;
  width: 10px;
  margin: 15px;
  height: 117px;
}
.card-text {
  margin-top: 5px;
  padding: 5px;
  text-align: center;
  font-size: 13px;
}
.card-text-data {
  padding: 5px;
  text-align: center;
  font-size: 13px;
}
</style>
