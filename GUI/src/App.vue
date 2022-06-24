<template>
  <div class="container-fluid" v-loading="apiCrash">
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
import { exec, execFile } from "child_process"
import Menu from '@/components/Menu'
import Plotly from '@/components/Plotly'

export default {
  setup() {
    const globalStore = useGlobalStore();
    const plotlyStore = usePlotlyStore();
    const { process, responseStacks, responseStringCache, apiCrash } = storeToRefs(useGlobalStore())
    return {
      process,
      responseStacks,
      responseStringCache,
      apiCrash,
      globalStore,
      plotlyStore
    }
  },
  components: {
    Menu,
    Plotly,
  },
  beforeMount: async function () {
    let filePath = (require('app-root-dir').get()) + `\\extraResources\\Windows\\equation_drawing.exe`;
    if (this.globalStore.isMac) {
      filePath = (require('app-root-dir').get()) + '/extraResources/macOS/equation_drawing';
    }
    filePath = filePath.replace(/ /g, '\\ ');
    this.process = exec(filePath, {
      maxBuffer: 1024 * 2000000,
      encoding: 'utf8'
    });
    this.process.stdout.on("data", (response) => {
      this.receiveData(response);
    })
    this.process.stdout.on("end", async () => {
      await this.globalStore.waitAllReqCompleted(true);
    });

    this.process.on('exit', async (code) => {
      this.apiCrash = true;
      if (this.globalStore.apiConsole) {
        console.log(`child process exited with code ${code}`);
        console.log(`api crash, start restore api`);
      }
      // remove listeners
      this.process.removeAllListeners();
      // restart binary
      this.process = exec(filePath, {
        maxBuffer: 1024 * 2000000,
        encoding: 'utf8'
      });
      this.process.stdout.on("data", (response) => {
        this.receiveData(response);
      })

      // filter completed request
      const completedRequest = this.responseStacks.filter(e => e.completed);

      // restore
      this.responseStacks = [];
      this.responseStringCache = '';
      for (let index = 0; index < completedRequest.length; index ++) {
        const request = completedRequest[index];
        await this.globalStore.waitAllReqCompleted();
        this.responseStacks.push({
          method: request.method,
          commend: request.commend,
          token: request.token,
          completed: false,
          result: null,
          callback: () => {}
        });
        this.globalStore.apiSent(request.commend);
        if (this.globalStore.apiConsole) {
          console.log(`restore completed: ${request.commend}\n token: ${request.token}`);
        }
      }
      if (this.globalStore.apiConsole) {
        console.log(`
          ================================\n
          =======restore completed!!======\n
          ================================
        `);
      }
      setTimeout(() => {
        this.apiCrash = false;
      }, 5000);
    });
  },
  mounted() {

  },
  async beforeUnmount() {
    await this.globalStore.waitAllReqCompleted(true);
    this.globalStore.process.removeAllListeners();
  },
  methods: {
    receiveData(response, restore = false) {
      if (this.globalStore.apiConsole) {
        console.log('receiveData', response);
      }
      try {
        const data = JSON.parse(this.responseStringCache + response);
        let thisResponseIndex = this.responseStacks.map(e => e.token).indexOf(data.hash);
        if (thisResponseIndex > -1 && !this.responseStacks[thisResponseIndex].completed) {
          this.responseStringCache = "";
          this.responseStacks[thisResponseIndex].completed = true;
          this.responseStacks[thisResponseIndex].result = data;
          this.responseStacks[thisResponseIndex].callback(data);
        }
        if (this.globalStore.apiConsole) {
          console.log(data);
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
