<template>
  <div>
    <div v-if="!optionsList.length || loading">loading...</div>
    <template v-else-if="containsMissingData">
      <p>Oooops!! Seem there is no data at this place</p>
    </template>
    <highcharts
      v-else
      v-for="(options, index) in optionList"
      :options="options"
      ref="highcharts"
      class="chart"
      :key="index"
    ></highcharts>
  </div>
</template>

<script>
import Highcharts from 'highcharts'
import axios from 'axios'

export default {
  props: {
    sensorData: {
      required: true
    },
    device_id: {
      required: true
    }
  },
  watch: {
    async device_id(newVal) {
      this.loading = true
      this.fetchSensorData(newVal)
    }
  },
  data() {
    return {
      loading: true,
      containsMissingData: false,
      optionsList: []
    }
  },
  async mounted() {
    await this.fetchSensorData(this.device_id)
  },

  methods: {
    async fetchSensorData(device_id) {
      let promises = []

      this.sensorData.forEach(sensor_id => {
        promises.push(
          axios.get(
            `https://api.waziup.io/api/v2/sensors_data?device_id=${device_id}&sensor_id=${sensor_id}&sort=dsc&calibrated=true&limit=100`
          )
        )
      })

      let dataset = {}

      axios.all(promises).then(
        axios.spread((...responses) => {
          this.optionsList = responses.map(({ data }, i) => {
            if (!Array.isArray(data) || !data.length) return

            let unit = ''
            let name = ''

            dataset.data = data.map(({ date_received, value }) => {
              return [date_received, value]
            })
            switch (data[i].sensor_id) {
              case 'HUM':
                unit = '%'
                name = 'Humidity'
                break
              case 'sHm':
                unit = '%'
                name = 'Soil Humidity'
                break
              case 'PH':
                unit = ''
                name = 'Soil pH'
                break
              case 'RD':
                unit = 'Drops'
                name = 'Rain drops'
                break
              case 'SPD':
                unit = 'm/s'
                name = 'Wind Speed'
                break
              case 'TC':
                unit = '&deg; C'
                name = 'Temperature'
                break
              case 'DIR':
                unit = ''
                name = 'Wind Direction '
                break
              default:
                ;(unit = 'h'), (name = data[i].sensor_id)
            }

            dataset.name = name
            dataset.unit = unit
            dataset.type = 'line'
            dataset.color = Highcharts.getOptions().colors[i]
            return this.genOptions(this, dataset)
          })

          if (this.optionsList.length === 0) {
            this.containsMissingData = true
          } else {
            this.containsMissingData = false
          }
          this.loading = false
        })
      )
    },
    sync(vm, event, type) {
      vm.$refs.highcharts.forEach(({ chart }) => {
        if (chart === event.target.series.chart) return
        chart.series.forEach(series => {
          series.data.forEach(point => {
            if (point.x === event.target.x) {
              if (type === 'over') {
                point.setState('hover')
                chart.tooltip.refresh(point)
                chart.xAxis[0].drawCrosshair(event, point)
              } else {
                point.setState()
                chart.tooltip.hide()
                chart.xAxis[0].hideCrosshair()
              }
            }
          })
        })
      })
    },
    genOptions(charts, dataset) {
      return {
        chart: {
          marginLeft: 40, // Keep all charts left aligned
          spacingTop: 20,
          spacingBottom: 20
        },
        title: {
          text: dataset.name,
          align: 'left',
          margin: 0,
          x: 30
        },
        credits: {
          enabled: false
        },
        legend: {
          enabled: false
        },
        xAxis: {
          crosshair: true,
          type: 'datetime'
        },
        yAxis: {
          title: {
            text: null
          }
        },
        tooltip: {
          positioner: function() {
            return {
              // right aligned
              x: this.chart.chartWidth - this.label.width,
              y: 10 // align to title
            }
          },
          borderWidth: 0,
          backgroundColor: 'none',
          pointFormat: '{point.y}',
          headerFormat: '',
          shadow: false,
          style: {
            fontSize: '18px'
          },
          valueDecimals: dataset.valueDecimals
        },
        plotOptions: {
          series: {
            point: {
              events: {
                mouseOver: e => {
                  this.sync(charts, e, 'over')
                },
                mouseOut: e => {
                  this.sync(charts, e, 'out')
                }
              }
            }
          }
        },
        series: [
          {
            data: dataset.data,
            name: dataset.name,
            type: dataset.type,
            color: dataset.color,
            fillOpacity: 0.3,
            tooltip: {
              valueSuffix: ' ' + dataset.unit
            }
          }
        ]
      }
    }
  }
}
</script>

<style scoped>
.chart {
  min-width: 320px;
  max-width: 800px;
  height: 220px;
  margin: 0 auto;
}
</style>
