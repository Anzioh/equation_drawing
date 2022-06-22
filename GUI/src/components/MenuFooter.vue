<template>
  <div class="fsc">
    <p>Force Refresh</p>
    <p>Dev Team</p>
    <p>Source Code</p>
  </div>
</template>

<script>
export default {
name: "MenuFooter"
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