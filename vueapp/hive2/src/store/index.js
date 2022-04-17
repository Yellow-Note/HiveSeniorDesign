import { defineStore } from 'pinia'

export const useThemeStore = defineStore('Theme', {
  state: () => ({ theme: 'dark' }),
  getters: {
    double: state => state.count * 2,
  },
  actions: {
    increment() {
      this.count++
    },
  },
})
