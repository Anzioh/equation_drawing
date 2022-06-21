<template>
  <el-dropdown class="variable-dropdown" trigger="click">
    <span class="el-button">
      Click Me
    </span>
    <template #dropdown>
      <el-dropdown-menu>
        <el-dropdown-item class="clearfix">
          <el-icon class="el-icon"><EditPen /></el-icon>
          Modiify
        </el-dropdown-item>
        <el-popconfirm title="Are you sure to delete this?">
          <template #reference>
            <el-button :icon="Close">Delete</el-button>
          </template>
        </el-popconfirm>
      </el-dropdown-menu>
    </template>
  </el-dropdown>
</template>

<script>
  import { EditPen, Close } from '@element-plus/icons-vue';
  export default {
    setup() {
      return {
        EditPen,
        Close
      }
    }
  }
</script>
<style scoped>
  .el-button {
    width: 100% !important;
    border: none!important;
    outline: none!important;
    border-radius: 0!important;
    justify-content: flex-start;
    display: flex;
  }
  .el-button> .el-icon {
    margin-right: 5px!important;
  }
</style>