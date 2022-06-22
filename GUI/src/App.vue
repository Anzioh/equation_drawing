<template>
  <div class="container-fluid">
    <div class="row">
      <div class="col-3">
        <Menu></Menu>
      </div>
      <div class="col-9">
        <Plotly></Plotly>
      </div>
    </div>
  </div>
</template>

<script>
import { storeToRefs } from 'pinia'
import { useGlobalStore } from '@/store/global'
import { usePlotlyStore } from "@/store/plotly"
import { exec } from "child_process"
import Menu from '@/components/Menu'
import Plotly from '@/components/Plotly'

export default {
  setup() {
    const globalStore = useGlobalStore();
    const plotlyStore = usePlotlyStore();
    const { process, responseStacks, responseStringCache } = storeToRefs(useGlobalStore())
    return {
      process,
      responseStacks,
      responseStringCache,
      globalStore,
      plotlyStore
    }
  },
  components: {
    Menu,
    Plotly,
  },
  beforeMount() {
    this.globalStore.process = exec(`./src/assets/binary/${this.globalStore.isMac ? 'macOS' : 'Windows'}/equation_drawing${this.globalStore.isMac ? '' : '.exe'}`);
  },
  mounted() {
    this.globalStore.process.stdout.on("data", (response) => {
      this.receiveData(response);
    })
    this.globalStore.process.on('close', (code) => {
      console.log(`child process close all stdio with code ${code}`);
    });

    this.globalStore.process.on('exit', (code) => {
      console.log(`child process exited with code ${code}`);
    });
  },
  async beforeUnmount() {
    await this.globalStore.waitAllReqCompleted(true);
    this.globalStore.process.removeAllListeners();
  },
  methods: {
    receiveData(response) {
      try {
        const data = JSON.parse(this.responseStringCache + response);
        let thisResponseIndex = this.responseStacks.map(e => e.token).indexOf(data.hash);
        if (thisResponseIndex > -1 && !this.responseStacks[thisResponseIndex].completed) {
          this.responseStringCache = "";
          this.responseStacks[thisResponseIndex].completed = true;
          this.responseStacks[thisResponseIndex].callback(data);
          this.responseStacks[thisResponseIndex].result = data;
        }
      }catch (e) {
        this.responseStringCache += response; // push some json string to cache
      }
    }
  }
}
</script>

<style lang="scss">
#app {
  height: 100vh;
  overflow: hidden;
}
</style>
