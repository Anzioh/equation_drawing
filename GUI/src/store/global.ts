import { defineStore } from 'pinia'
import { exec } from 'node:child_process'
import { Request } from '@/models/request'
import { ref, toRaw } from 'vue'

export const useGlobalStore = defineStore('global', {
  state: () => {
    return {
      process: null,
      responseStacks: ref<Request[]>([]),
      responseStringCache: '', // if c++ return a very long json
      apiTimeOut: 10000,
    }
  },
  getters: {
    // check all the api has response
    checkAllSet: (state): boolean => {
      return state.responseStacks.every((e: Request) => {
        return e.completed
      })
    },
    isMac: (): boolean => {
      const os: string = window.navigator.platform;
      const result = Array(os.match(/Mac/gi)).length > 0;
      return result;
    }
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
    // get token
    getToken: function(): string {
      let random = [...Array(8).keys()].map(e => String.fromCharCode(Math.floor((Math.random() * (126 - 47)) + 48))).join("");
      let cacheToken = Date.now().toString(16) + random + "";
      let token = cacheToken.split('').sort((a, b) => Math.floor(Math.random() - 0.5)).join("");
      return token;
    },
    // get response log by token
    getResLogByToken: function(token: string): any {
      let result:any = false;
      this.responseStacks.forEach(response => {
        if (response.token == token) {
          result = response;
        }
      })
      return result;
    },
    // write by stdin
    apiSent: function (commend: string): void {
      const api:any = toRaw(this.process);
      api.stdin.write(commend + '\n');
    }
  },
})
