import { defineStore } from 'pinia'
import { Request } from '@/models/request'
import { Function } from '@/models/Function'
import { ref } from 'vue'

export const useFunctionStore = defineStore('functions', {
  state: () => ({
    functions: ref<Function[]>([]),
  }),
})
