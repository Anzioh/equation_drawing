<template>
  <div class="container-fluid">
    <div class="row">
      <div class="col-3">
        <Menu></Menu>
      </div>
      <div class="col-9">
        <Draw></Draw>
      </div>
    </div>
  </div>
</template>

<script>
import { storeToRefs } from 'pinia'
import { useGlobalStore } from '@/store/global'
import { usePlotlyStore } from "@/store/plotly";
import Menu from '@/components/Menu'
import Draw from '@/components/Draw'

export default {
  setup() {
    const globalStore = useGlobalStore();
    const plotlyStore = usePlotlyStore();
    const { process } = storeToRefs(useGlobalStore())
    return {
      process,
      globalStore,
      plotlyStore
    }
  },
  components: {
    Menu,
    Draw,
  },
  mounted() {
    console.log(this.process);
  },
}
</script>

<style lang="scss">
#app {
  height: 100vh;
  overflow: hidden;
}
</style>
