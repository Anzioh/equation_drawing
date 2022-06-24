const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  chainWebpack: (config) => {
    config.target('electron-renderer')
  },
  pluginOptions: {
    electronBuilder: {
      builderOptions: {
        "productName": "bla plotter",
        "appId": "apple1314520iphone@icloud.com",
        "copyright": "Copyright © 2021–2022 blabla Team",
        "directories":  {
          "output": "build"
        },
        "extraResources": [
          {
            "from": "./extraResources/",
            "to": "extraResources"
          }
        ],
        "mac": {
          "icon": "public/icon.icns",
          "target": "dmg"
        },
        "win": {
          "asar": false,
          "target": "nsis",
          "icon": "public/icon.ico"
        },
        "nsis": {
          "installerIcon": "public/icon.ico",
          "installerHeaderIcon": "public/icon.ico",
          "deleteAppDataOnUninstall": true
        }
      }
    }
  }
})
