<template>
  <div id="equation">
    <div class="pretty-card">
      <el-color-picker v-model="color" show-alpha />
      <div class="content">
        <p>y=x^2</p>
      </div>
      <div class="control">
        <el-button icon="EditPen" plain size="small" circle />
      </div>
    </div>
  </div>
</template>
<script>
  import { storeToRefs } from 'pinia';
  import { useGlobalStore } from "@/store/global";
  import { usePlotlyStore } from "@/store/plotly";

  export default {
    data() {
      return {
        color: "#aabbcc"
      }
    },
    setup() {
      const globalStore = useGlobalStore();
      const plotlyStore = usePlotlyStore();
      return {
        globalStore,
        plotlyStore
      }
    },
    methods: {

    }
  }
</script>

<style scoped>

</style>