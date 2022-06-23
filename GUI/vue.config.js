const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  chainWebpack: (config) => {
    config.target('electron-renderer')
  },
  pluginOptions: {
    // pluginOptions: {
    //   electronBuilder: {
    //     mainProcessFile: 'src/myBackgroundFile.js', // 主進程進入點
    //     rendererProcessFile: 'src/myMainRenderFile.js', // 渲染進程進入點
    //     outputDir: 'electron-builder-output-dir', // 編譯資料夾
    //     preload: 'src/preload.js', // preload 檔案位置
    //     builderOptions: {
    //       asar: false, // 是否使用 asar 壓縮檔案
    //       appId: 'apple1314520iphone@icloud.com', // 認證的 appId
    //       productName: 'bla plotter', // 專案名稱
    //       artifactName: '${name}.${ext}', // 檔案名稱樣板，有 ESLint 記得關掉
    //       copyright: 'Copyright©CaseyWang, Anzioh, yehhenry', // 版權
    //       // Windows 相關設定
    //       win: {
    //         legalTrademarks: 'legalTrademarks', // 商標
    //         icon: 'public/icon.ico', // 安裝檔圖示
    //         target: [{
    //           target: 'nsis', // 檔案類型
    //           arch: ['x64', 'ia32'] // 檔案位元，越多類型檔案越大
    //         }]
    //       },
    //       // DMG 相關設定
    //       dmg: {
    //         icon: 'public/icon.icns' // 安裝檔圖示
    //       },
    //       // Linux 相關設定
    //       linux: {
    //         icon: 'public/icon.png' // 安裝檔圖示
    //       },
    //       // macOS 相關設定
    //       mac: {
    //         icon: 'public/icon.icns' // 安裝檔圖示
    //       },
    //       nsis: {
    //         oneClick: false, // 是否一鍵安裝
    //         perMachine: true, // 是否為每一台機器安裝
    //         installerIcon: 'public/icon.ico', // 安裝圖示
    //         uninstallerIcon: 'public/icon.ico', // 卸載圖示
    //         installerHeaderIcon: 'public/icon.ico', // 安裝頂部圖示
    //         allowToChangeInstallationDirectory: true, // 是否可更改安裝目錄
    //         include: 'installer.nsh', // 設定檔路徑
    //         createDesktopShortcut: true, // 是否建立桌面捷徑
    //         createStartMenuShortcut: true // 是否建立開始捷徑
    //       }
    //     }
    //   }
    // }
  }
})
