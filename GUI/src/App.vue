<template>
  <div class="container-fluid">
    <div class="row">
      <div class="col-3">
        <Menu></Menu>
        <Draw></Draw>
      </div>
    </div>
  </div>
</template>
<script>
import { storeToRefs } from 'pinia';
import { useGlobalStore } from "@/store/global";
import Menu from '@/components/Menu';
import Draw from "@/components/Draw";
export default {
  setup() {
    const { process } = storeToRefs(useGlobalStore());
    return {
      process
    }
  },
  components: {
    Menu,
    Draw
  },
  mounted() {
    console.log(this.process);
  }
}
</script>
<style lang="scss">
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

nav {
  padding: 30px;

  a {
    font-weight: bold;
    color: #2c3e50;

    &.router-link-exact-active {
      color: #42b983;
    }
  }
}
</style>
