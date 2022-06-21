<template>
  <div id="menu">
    <div class="vh-10 pt-4 pb-4">
      <img class="h-100 float-start" :src="require('@/assets/logo.svg')" alt="" />
    </div>
    <div class="vh-45">
      <div class="fbc">
        <p class="m-0 text-secondary">方程組</p>
        <el-button size="small" type="primary" icon="Plus" @click="addEquation" circle plain></el-button>
      </div>
      <Equation v-for="item in equations" :data="item" @delEquation="api_delEquation"></Equation>
    </div>
    <div class="vh-45">
      <div class="fbc">
        <p class="m-0 text-secondary">變量</p>
        <el-button size="small" type="primary" icon="Plus" @click="variableModalDisplay = true" circle plain></el-button>
      </div>
      <Variable></Variable>
      <el-dialog v-model="variableModalDisplay" title="Add a variable" width="40%">
<!--    TODO: variableModal content    -->
      </el-dialog>
    </div>
  </div>
</template>

<script>
  import { storeToRefs } from "pinia";
  import { useGlobalStore } from "@/store/global";
  import { usePlotlyStore } from "@/store/plotly";
  import Equation from "@/components/Equation";
  import Variable from "@/components/Variable";
  import { ElMessage, ElMessageBox, ElNotification } from 'element-plus';
  export default {
    setup() {
      const globalStore = useGlobalStore();
      const plotlyStore = usePlotlyStore();
      const { process, responseStacks } = storeToRefs(useGlobalStore());
      const { equations, variableModalDisplay } = storeToRefs(usePlotlyStore());
      return {
        globalStore,
        plotlyStore,
        process,
        responseStacks,
        equations,
        variableModalDisplay
      }
    },
    components: {
      Equation,
      Variable
    },
    methods: {
      async addEquation() {
        ElMessageBox.prompt('enter your equation: ', 'Add Equation', {
          confirmButtonText: 'Add',
          cancelButtonText: 'Cancel',
          beforeClose: async (action, instance, done) => {
            if (action === 'confirm') {
              if (! instance.inputValue) {
                ElMessage({
                  type: 'error',
                  message: 'field should have text'
                })
                return;
              }
              instance.confirmButtonLoading = true;
              instance.confirmButtonText = 'Loading...';
              // call c++ API
              const token = await this.api_addEquation(instance.inputValue);
              let interval = setInterval(() => {
                const response = this.globalStore.getResLogByToken(token);
                if (response) {
                  if (response.completed) {
                    // has completed
                    clearInterval(interval);
                    setTimeout(() => {
                      instance.confirmButtonLoading = false
                      instance.confirmButtonText = 'Add'
                    }, 300);
                    const data = response.result;
                    if (data.isError) {
                      ElMessage({
                        type: 'error',
                        message: data.errorMessage
                      })
                    }
                    else {
                      this.equations.push({
                        id: data.id,
                        color: this.plotlyStore.getRandomColor(),
                        equation: data.equation,
                        srcEquation: instance.inputValue,
                        x: [],
                        y: [],
                        tokenList: [token]
                      });
                      done();
                    }
                  }
                }
              },1000)
            } else {
              done()
            }
          },
        }).then((action) => {
          // action
          if (action === 'confirm') {
            ElMessage({
              type: 'success',
              message: 'Add Success',
            })
          }
        }).catch(() => {
          ElMessage({
            type: 'info',
            message: 'Input canceled',
          })
        })
      },
      async api_addEquation(equation) {
        equation = equation == null ? "" : equation;
        await this.globalStore.waitAllReqCompleted();
        const token = this.globalStore.getToken();
        const commend = `addEquation ${token} ${equation.replace(/\s/g, '')}`;
        this.responseStacks.push({
          method: "addEquation",
          commend: commend,
          token: token,
          completed: false,
          result: null,
          callback: () => {}
        });
        this.globalStore.apiSent(commend);
        return token;
      },
      async api_delEquation(id) {
        await this.globalStore.waitAllReqCompleted();
        const token = this.globalStore.getToken();
        const commend = `delEquation ${token} ${id}`;
        this.responseStacks.push({
          method: "delEquation",
          commend: commend,
          token: token,
          completed: false,
          result: null,
          callback: () => {}
        });
        this.globalStore.apiSent(commend);
        return token;
      },
      async addVariable() {

      },
      async api_addVariable(equation) {
        await this.globalStore.waitAllReqCompleted();
        const token = this.globalStore.getToken();
        const commend = `addVar ${token} ${equation}`;
        this.responseStacks.push({
          method: "addEquation",
          commend: commend,
          token: token,
          completed: false,
          result: null,
          callback: () => {}
        });
        this.globalStore.apiSent(commend);
        return token;
      },
      async api_delVariable(id) {
        await this.globalStore.waitAllReqCompleted();
        const token = this.globalStore.getToken();
        const commend = `delVar ${token} ${id}`;
        this.responseStacks.push({
          method: "delEquation",
          commend: commend,
          token: token,
          completed: false,
          result: null,
          callback: () => {}
        });
        this.globalStore.apiSent(commend);
        return token;
      }
    }
  }
</script>

<style scoped>
#menu {
  height: 100vh;
  padding: 15px 30px 30px 15px;
  background-color: rgb(251, 251, 251);
}
#menu:after {
  content: '';
  position: absolute;
  top: 0;
  left: -15px;
  height: 100vh;
  width: 15px;
  background-color: rgb(251, 251, 251);
}
</style>
