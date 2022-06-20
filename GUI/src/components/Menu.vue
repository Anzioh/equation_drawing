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
      <Equation></Equation>
    </div>
    <div class="vh-45">
      <div class="fbc">
        <p class="m-0 text-secondary">變量</p>
        <el-button size="small" type="primary" icon="Plus" circle plain></el-button>
      </div>
      <Variable></Variable>
    </div>
  </div>
</template>

<script>
  import { useGlobalStore } from "@/store/global";
  import Equation from "@/components/Equation";
  import Variable from "@/components/Variable";
  import { ElMessage, ElMessageBox } from 'element-plus';
  export default {
    components: {
      Equation,
      Variable
    },
    methods: {
      addEquation() {
        ElMessageBox.prompt('enter your equation: ', 'Add Equation', {
          confirmButtonText: 'Add',
          cancelButtonText: 'Cancel',
          beforeClose: (action, instance, done) => {
            if (action === 'confirm') {
              instance.confirmButtonLoading = true
              instance.confirmButtonText = 'Loading...'
              setTimeout(() => {
                done()
                setTimeout(() => {
                  instance.confirmButtonLoading = false
                }, 300)
              }, 3000)
            } else {
              done()
            }
          },
        }).then((action) => {
          ElMessage({
            type: 'info',
            message: `action: ${action}`,
          })
        }).catch(() => {
          ElMessage({
            type: 'info',
            message: 'Input canceled',
          })
        })
      },
      editEquation(id) {

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
