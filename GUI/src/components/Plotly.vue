<template>
  <div id="plotly"></div>
</template>
<script>
import {ref, toRaw} from 'vue'
import { storeToRefs } from 'pinia'
import { usePlotlyStore } from "@/store/plotly"
import Plotly from 'plotly.js'

export default {
  setup() {
    const { plotly, plotlyDOM, plotlyData, plotlyLayout, plotlyOption, plotlyRange, equations } = storeToRefs(usePlotlyStore());
    const plotlyStore = ref(usePlotlyStore());
    return {
      plotly,
      plotlyDOM,
      plotlyStore,
      plotlyData,
      plotlyLayout,
      plotlyOption,
      plotlyRange,
      equations
    }
  },
  components: {
  },
  mounted() {
    this.plotlyDOM = this.$el;
    Plotly.newPlot(this.plotlyDOM, [], this.plotlyLayout, this.plotlyOption);

    // on plotly resize;
    this.plotlyDOM.on("plotly_relayout", (e) => {
      this.plotlyRange.x.start = e['xaxis.range[0]'];
      this.plotlyRange.x.end = e['xaxis.range[1]'];
      this.plotlyRange.y.start = e['yaxis.range[0]'];
      this.plotlyRange.y.end = e['yaxis.range[1]'];
    })
  },
  methods: {
    update() {
      let data = [];
      toRaw(this.equations).forEach(equation => {
        if (!(equation.x.length <= 0 || equation.y.length <= 0)) {
          data.push({
            name: equation.srcEquation,
            type: 'scatter',
            x: equation.x,
            y: equation.y,
            mode: 'lines',
            connectgaps: false,
            marker: {
              color: equation.color,
            },
            line: {
              color: equation.color,
              width: 4
            }
          })
        }
      })
      this.plotlyLayout.xaxis.range = [this.plotlyRange.x.start, this.plotlyRange.x.end];
      this.plotlyLayout.yaxis.range = [this.plotlyRange.y.start, this.plotlyRange.y.end];
      Plotly.react(this.$el, data, this.plotlyLayout, this.plotlyOption);
    }
  },
  watch: {
    equations: {
      handler() {
        this.update();
      },
      deep: true
    }
  }
}
</script>
<style scoped>
#plotly {
  height: 100vh;
  width: 100%;
  padding-top: 30px;
  padding-bottom: 30px;
}
</style>