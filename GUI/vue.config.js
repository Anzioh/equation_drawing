const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  chainWebpack: (config) => {
    config.target('electron-renderer')
  },
  pluginOptions: {
    electronBuilder: {
      preload: 'src/preload.js'
    }
  }
})
