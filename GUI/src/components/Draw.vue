<template></template>
<script>
import { ref, reactive } from 'vue'
import { Plotly } from 'vue-plotly'

export default {
  setup() {
    const data = reactive([
      {
        x: [1, 2, 3, 4],
        y: [10, 15, 13, 17],
        type: 'scatter',
      },
    ])
    const layout = reactive({
      title: 'My graph',
    })
    return {
      data,
      layout,
    }
  },
  components: {
    Plotly,
  },
}
</script>
