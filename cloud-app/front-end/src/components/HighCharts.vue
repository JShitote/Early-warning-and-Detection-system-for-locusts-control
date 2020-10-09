<template>
  <div>
    <div v-if="!optionsList.length">loading...</div>
    <highcharts
      v-else
      v-for="(options, index) in optionsList"
      :options="options"
      ref="highcharts"
      class="chart"
      :key="index"
    ></highcharts>
  </div>
</template>

<script>
import Highcharts from 'highcharts'

export default {
  data() {
    return {
      chartOptions: {
        series: [
          {
            data: [1, 2, 3] // sample data
          }
        ]
      },
      optionsList: []
    }
  },
  mounted() {
    this.fetchData();
  },
  methods: {
    fetchData() {
      fetch(
        'https://cdn.jsdelivr.net/gh/highcharts/highcharts@v6.0.4/samples/data/activity.json'
      )
        .then(res => res.json())
        .then(activity => {
          this.optionsList = activity.datasets.map((dataset, i) => {
            dataset.data = dataset.data.map((val, j) => [
              activity.xData[j],
              val
            ])
            dataset.color = Highcharts.getOptions().colors[i]
            // return this.genOptions(vm, dataset)
            return this.genOptions(this, dataset)
          })
        })
    },
    sync(vm, event, type) {
      vm.$refs.highcharts.forEach(function({ chart }){
       
        if (chart === this.series.chart) return
        chart.series.forEach(series => {
          series.data.forEach(point => {
            if (point.x === this.x) {
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
    genOptions(vm, dataset) {
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
          labels: {
            format: '{value} km'
          }
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
                mouseOver: (event) =>{
                  // this.sync.call(this, vm, event, 'over')
                  
                  this.sync(this, event, 'over')
                },
                mouseOut: (event)=> {
                  this.sync(this, event, 'out')
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
