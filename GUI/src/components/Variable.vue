<template>
  <el-tooltip effect="dark" :content="data.srcContent" placement="top">
    <el-dropdown size="small" split-button type="primary" class="variable-dropdown" trigger="click">
      <span>
        {{ data.name }}
      </span>
      <template #dropdown>
        <el-dropdown-menu>
          <el-dropdown-item class="clearfix" @click="$emit('editVariable', data)">
            <el-icon class="el-icon"><EditPen /></el-icon>
            Modify
          </el-dropdown-item>
          <el-popconfirm title="Are you sure to delete this?" @confirm="$emit('delVariable', data.id)">
            <template #reference>
              <el-button size="small" :icon="Close"> Delete</el-button>
            </template>
          </el-popconfirm>
        </el-dropdown-menu>
      </template>
    </el-dropdown>
  </el-tooltip>
</template>

<script>
  import { EditPen, Close } from '@element-plus/icons-vue';
  export default {
    setup() {
      return {
        EditPen,
        Close
      }
    },
    props: {
      data: Object
    }
  }
</script>
<style scoped>
  .variable-dropdown {
    margin-top: 5px;
    margin-right: 5px;
  }
  .variable-dropdown .el-button--small [class*=el-icon]+span {
    margin-left: 6px!important;
    font-weight: 300!important;
  }
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