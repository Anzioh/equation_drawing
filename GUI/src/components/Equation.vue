<template>
  <div class="pretty-card">
    <el-color-picker v-model="color" show-alpha />
    <div class="content">
      <p>{{ srcEquation }}</p>
    </div>
    <div class="control">
      <el-button icon="EditPen" plain size="small" @click="editEquation" circle />
    </div>
  </div>
</template>
<script>
  import { storeToRefs } from 'pinia';
  import { useGlobalStore } from "@/store/global";
  import { usePlotlyStore } from "@/store/plotly";
  import {ElMessage, ElMessageBox} from "element-plus";

  export default {
    props: {
      id: Number,
      equation: String,
      srcEquation: String,
      color: String,
      tokenList: Array
    },
    setup() {
      const globalStore = useGlobalStore();
      const plotlyStore = usePlotlyStore();
      const { responseStacks } = storeToRefs(useGlobalStore());
      const { equations } = storeToRefs(usePlotlyStore());
      return {
        globalStore,
        plotlyStore,
        responseStacks,
        equations
      }
    },
    methods: {
      editEquation() {
        ElMessageBox.prompt('enter your equation: ', 'Modify Equation', {
          confirmButtonText: 'Modify',
          cancelButtonText: 'Cancel',
          inputValue: this.equation,
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
              const token = await this.api_editEquation(instance.inputValue);
              let interval = setInterval(() => {
                const response = this.globalStore.getResLogByToken(token);
                if (response) {
                  if (response.completed) {
                    // has completed
                    clearInterval(interval);
                    setTimeout(() => {
                      instance.confirmButtonLoading = false
                      instance.confirmButtonText = 'Modify'
                    }, 300);
                    const data = response.result;
                    if (data.isError) {
                      ElMessage({
                        type: 'error',
                        message: data.errorMessage
                      })
                    }
                    else {
                      this.tokenList.push(data.hash);
                      this.srcEquation = instance.inputValue;
                      this.equation = data.equation;
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
      async api_editEquation(equation) {
        await this.globalStore.waitAllReqCompleted();
        const token = this.globalStore.getToken();
        const commend = `editEquation ${token} ${this.id} ${equation.replace(/\s/g, '')}`;
        this.responseStacks.push({
          method: "editEquation",
          commend: commend,
          token: token,
          completed: false,
          result: null,
          callback: () => {}
        });
        this.globalStore.apiSent(commend);
        console.log(commend);
        return token;
      }
    },

  }
</script>