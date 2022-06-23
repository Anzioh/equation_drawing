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
      <div class="long-content">
        <Equation v-for="item in equations" :data="item" @api_getLine="api_getLine" @delEquation="api_delEquation"></Equation>
      </div>
    </div>
    <div class="vh-40">
      <div class="fbc" style="background: rgba(251, 251, 251, .4)">
        <p class="m-0 text-secondary">變量</p>
        <el-button size="small" type="primary" icon="Plus" @click="addVariable" circle plain></el-button>
      </div>
      <div class="long-content">
        <Variable v-for="item in variables" :data="item" @editVariable="editVariable" @delVariable="api_delVariable"></Variable>
      </div>
    </div>
    <div class="vh-5">
      <MenuFooter></MenuFooter>
    </div>
  </div>
</template>

<script>
  import { storeToRefs } from "pinia";
  import { useGlobalStore } from "@/store/global";
  import { usePlotlyStore } from "@/store/plotly";
  import Equation from "@/components/Equation";
  import Variable from "@/components/Variable";
  import MenuFooter from "@/components/MenuFooter";
  import { ElMessage, ElMessageBox } from 'element-plus';
  import {toRaw} from "vue";
  export default {
    setup() {
      const globalStore = useGlobalStore();
      const plotlyStore = usePlotlyStore();
      const { process, responseStacks } = storeToRefs(useGlobalStore());
      const { equations, variables, plotlyRange, dpi } = storeToRefs(usePlotlyStore());
      return {
        globalStore,
        plotlyStore,
        process,
        responseStacks,
        equations,
        variables,
        plotlyRange,
        dpi
      }
    },
    components: {
      Equation,
      Variable,
      MenuFooter
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
              const newEquation = instance.inputValue.replace(/\s/ig, '');
              const token = await this.api_addEquation(newEquation);
              let interval = setInterval(async () => {
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
                    } else {
                      this.equations.push({
                        id: data.id,
                        color: this.plotlyStore.getRandomColor(),
                        equation: data.equation,
                        srcEquation: instance.inputValue,
                        x: [],
                        y: [],
                        tokenList: [token]
                      });
                      await this.api_getLine(data.id);
                      done();
                    }
                  }
                }
              }, 1000)
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
          callback: () => {
            this.equations = this.equations.filter(equation => {
              return equation.id != id;
            });
            ElMessage.success('Delete equation success');
          }
        });
        this.globalStore.apiSent(commend);
        return token;
      },
      async addVariable() {
        ElMessageBox.prompt('enter your variable: ', 'Add Variable', {
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
              const newEquation = instance.inputValue.replace(/\s/ig, '');
              const token = await this.api_addVariable(newEquation);
              let interval = setInterval(async () => {
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
                      this.variables.push({
                        id: data.id,
                        name: data.equation.split("=")[0],
                        content: data.equation,
                        srcContent: newEquation,
                        tokenList: [token]
                      });
                      await this.api_getAllLine();
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
      async editVariable(data) {
        ElMessageBox.prompt('enter your Variable: ', 'Modify Variable', {
          confirmButtonText: 'Modify',
          cancelButtonText: 'Cancel',
          inputValue: data.srcContent,
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
              const newEquation = instance.inputValue.replace(/\s/ig, '');
              const token = await this.api_editVariable(data, newEquation);
              let interval = setInterval(async () => {
                const response = this.globalStore.getResLogByToken(token);
                if (response) {
                  if (response.completed) {
                    // has completed
                    clearInterval(interval);
                    setTimeout(() => {
                      instance.confirmButtonLoading = false
                      instance.confirmButtonText = 'Modify'
                    }, 300);
                    const resData = response.result;
                    if (resData.isError) {
                      ElMessage({
                        type: 'error',
                        message: resData.errorMessage
                      })
                    }
                    else {
                      ElMessage({
                        type: 'success',
                        message: 'Modify variable success'
                      })
                      data.name = resData.equation.split("=")[0];
                      data.tokenList.push(resData.hash);
                      data.srcContent = instance.inputValue;
                      data.content = newEquation;
                      await this.api_getAllLine();
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
              message: 'Modify Success',
            })
          }
        }).catch(() => {
          ElMessage({
            type: 'info',
            message: 'Input canceled',
          })
        })
      },
      async api_editVariable(data, newContent) {
        await this.globalStore.waitAllReqCompleted();
        const token = this.globalStore.getToken();
        const commend = `editVar ${token} ${data.id} ${newContent}`;
        this.responseStacks.push({
          method: "editVariable",
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
          callback: (result) => {
            if (result.isError) {
              ElMessage.error(result.errorMessage);
            }else {
              this.variables = this.variables.filter(variable => {
                return variable.id != id;
              });
              ElMessage.success('Delete variable success');
            }
          }
        });
        this.globalStore.apiSent(commend);
        return token;
      },
      async api_getLine(id) {
        await this.globalStore.waitAllReqCompleted();
        const token = this.globalStore.getToken();
        const range = toRaw(this.plotlyRange);
        if (
          range.x.start == undefined || 
          range.x.end == undefined || 
          range.y.start == undefined || 
          range.y.end == undefined
        ) {
          return;
        }
        const rangeStr = `${range.x.start.toFixed(10)} ${range.x.end.toFixed(10)} ${range.y.start.toFixed(10)} ${range.y.end.toFixed(10)}`;
        const commend = `getLine ${token} ${id} ${this.dpi} ${rangeStr}`;
        this.responseStacks.push({
          method: "getLine",
          commend: commend,
          token: token,
          completed: false,
          result: null,
          callback: (result) => {
            const index = this.plotlyStore.getEquationIndex(id);
            if (index !== -1) {
              this.equations[index].x = result.x;
              this.equations[index].y = result.y;
              this.equations[index].tokenList.push(result.hash);
            }
          }
        });
        this.globalStore.apiSent(commend);
        return token;
      },
      async api_getAllLine() {
        if (this.equations.length === 0) {
          return;
        }
        await this.globalStore.waitAllReqCompleted();
        const token = this.globalStore.getToken();
        const range = toRaw(this.plotlyRange);
        if (
          range.x.start == undefined || 
          range.x.end == undefined || 
          range.y.start == undefined || 
          range.y.end == undefined
        ) {
          return;
        }
        const rangeStr = `${range.x.start.toFixed(10)} ${range.x.end.toFixed(10)} ${range.y.start.toFixed(10)} ${range.y.end.toFixed(10)}`;
        const commend = `getAllLine ${token} ${this.dpi} ${rangeStr}`;
        this.responseStacks.push({
          method: "getAllLine",
          commend: commend,
          token: token,
          completed: false,
          result: null,
          callback: (result) => {
            result.equations.forEach(e => {
              const index = this.plotlyStore.getEquationIndex(e.id);
              if (index !== -1) {
                this.equations[index].x = e.x;
                this.equations[index].y = e.y;
                this.equations[index].tokenList.push(result.hash);
              }
            })
          }
        });
        this.globalStore.apiSent(commend);
        return token;
      }
    },
    watch: {
      plotlyRange: {
        async handler() {
          await this.api_getAllLine();
        },
        deep: true
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
  .long-content {
    height: calc(100% - 15px) !important;
    overflow-y: auto!important;
    padding: 0 15px;
    margin-left: -15px;
    width: calc(100% + 30px);
  }
</style>
