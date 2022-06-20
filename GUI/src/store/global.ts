import { defineStore } from 'pinia'
import child_process from 'child_process'
import { Request } from '@/models/request'
import { ref } from 'vue'

const os = window.navigator.platform
const isMac = os.match(/Mac/gi)

export const useGlobalStore = defineStore('global', {
  state: () => {
    return {
      process: child_process.execFile(
        `./assets/binary/${isMac ? 'macOS' : 'Windows'}/equation_drawing${
          isMac ? '' : '.exe'
        }`
      ),
      responseStacks: ref<Request[]>([]),
      responseStringCache: '', // if c++ return a very long json
      apiTimeOut: 5000,
    }
  },
  getters: {
    // check all the api has response
    checkAllSet: (state): boolean => {
      return state.responseStacks.every((e: Request) => {
        return e.completed
      })
    },
  },
  actions: {
    // wait all the request are completed
    waitAllReqCompleted: async function (forceCompleted: boolean = false) {
      await new Promise<void>((resolve) => {
        const timeOut = setTimeout(() => {
          // force complete all response
          if (!this.checkAllSet) {
            let fails: Request[] = []
            this.responseStacks = this.responseStacks.map((e: Request) => {
              if (!e.completed) {
                fails.push(e)
              }
              if (forceCompleted) {
                e.completed = true
              }
              return e
            })
            clearTimeout(timeOut)
            clearInterval(interval)
            console.error(
              'ERROR: API response time out',
              fails,
              this.responseStacks
            )
          }
          resolve()
        }, this.apiTimeOut)
        const interval = setInterval(() => {
          if (this.checkAllSet) {
            clearInterval(interval)
            clearTimeout(timeOut)
            resolve()
          }
        }, 50)
        if (this.checkAllSet) {
          clearInterval(interval)
          clearTimeout(timeOut)
          resolve()
        }
      })
    },
  },
})
