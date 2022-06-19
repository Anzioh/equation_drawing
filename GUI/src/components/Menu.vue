<template>
  <div id="menu">
    <div class="vh-10 pt-4 pb-4">
      <img class="h-100 float-start" :src="require('@/assets/logo.svg')" alt="">
    </div>
    <div class="vh-45">
      <div class="fbc">
        <p class="m-0 text-secondary">方程組</p>
        <el-button size="small" type="primary" icon="Plus" circle plain></el-button>
      </div>

    </div>
    <div class="vh-45">
      <div class="fbc">
        <p class="m-0 text-secondary">變量</p>
        <el-button size="small" type="primary" icon="Plus" circle plain></el-button>
      </div>

    </div>
  </div>
</template>
<style scoped>
  #menu {
    height: 100vh;
    padding: 15px 30px 30px 15px;
    background-color: rgb(251, 251, 251);
  }
</style>