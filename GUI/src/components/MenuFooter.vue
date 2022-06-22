<template>
  <div class="fsc">
    <p @click="mess(`Haven't development`)">Force Refresh</p>
    <p @click="mess(`Haven't development`)">Dev Team</p>
    <p @click="mess(`Haven't development`)">Source Code</p>
  </div>
</template>

<script>
import {ElMessage} from "element-plus";

export default {
  name: "MenuFooter",
  methods: {
    mess(text) {
      ElMessage.warning(text);
    }
  }
}
</script>

<style scoped>
  p {
    font-size: 12px;
    margin-bottom: 0;
    color: #909399;
    margin-right: 7.5px;
    padding-right: 7.5px;
    border-right: 1px rgba(0, 0, 0, .3) solid;
    transition: .15s ease-in-out;
    cursor: pointer;
  }
  p:last-child {
    margin-right: 0;
    padding-right: 0;
    border: unset;
  }
  p:hover {
    color: var(--el-color-primary);
  }
</style>