<template>
  <div id="plotly"></div>
</template>
<script>
import { ref, watch } from 'vue'
import { storeToRefs } from 'pinia'
import { usePlotlyStore } from "@/store/plotly"
import Plotly from 'plotly.js'

export default {
  setup() {
    const { plotly, plotlyDOM, plotlyData, plotlyLayout, plotlyOption } = storeToRefs(usePlotlyStore());
    const plotlyStore = ref(usePlotlyStore());
    return {
      plotly,
      plotlyDOM,
      plotlyStore,
      plotlyData,
      plotlyLayout,
      plotlyOption
    }
  },
  components: {
  },
  mounted() {
    this.plotlyDOM = this.$el;
    // fake data
    const 解析度 = 10000;
    const 軸範圍 = {
      x: {
        start: -5,
        end: 5
      },
      y: {
        start: -5,
        end: 5
      }
    }
    // if function is f(x) = y = x^2
    const 起點 = 軸範圍.x.start; // if function
    const 終點 = 軸範圍.x.end;
    let allPoints = [];
    for (let index = 起點; index <= 終點; index += (終點 -  起點) / 解析度) {
      // 解析所有的x, y points
      const y = Math.sin(index);
      const x = index;
      allPoints.push({
        x: x,
        y: y
      })
    }
    this.plotly = Plotly.newPlot(this.plotlyDOM, [{
      name: 'y=x^2',
      type: 'scatter',
      x: allPoints.map(e => e.x),
      y: allPoints.map(e => e.y)
    }], this.plotlyLayout, this.plotlyOption)
    this.plotlyDOM.on("plotly_relayout", function(e) {
      console.log("plotly_relayout", e);
    })
  },
  watch: {

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