import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import api from '@/api'
import router from '@/router'

interface LoginData {
  token: string
  userId: number
  username: string
  playerId: number
  playerName: string
  sex: string
  isNewPlayer: boolean
}

export const useAuthStore = defineStore('auth', () => {
  const token = ref<string>(localStorage.getItem('token') || '')
  const userId = ref<number>(Number(localStorage.getItem('userId')) || 0)
  const username = ref<string>(localStorage.getItem('username') || '')
  const playerId = ref<number>(Number(localStorage.getItem('playerId')) || 0)
  const playerName = ref<string>(localStorage.getItem('playerName') || '')
  const sex = ref<string>(localStorage.getItem('sex') || 'm')

  const isAuthenticated = computed(() => !!token.value)

  async function login(loginData: { username: string; password: string }) {
    const res: any = await api.post('/auth/login', loginData)
    const data = res.data as LoginData
    setLoginData(data)
    return data
  }

  async function register(registerData: {
    username: string
    password: string
    sex: string
    playerName: string
  }) {
    const res: any = await api.post('/auth/register', registerData)
    const data = res.data as LoginData
    setLoginData(data)
    return data
  }

  async function changePassword(data: {
    username: string
    oldPassword: string
    newPassword: string
  }) {
    await api.post('/auth/password', data)
  }

  function setLoginData(data: LoginData) {
    token.value = data.token
    userId.value = data.userId
    username.value = data.username
    playerId.value = data.playerId
    playerName.value = data.playerName
    sex.value = data.sex

    localStorage.setItem('token', data.token)
    localStorage.setItem('userId', String(data.userId))
    localStorage.setItem('username', data.username)
    localStorage.setItem('playerId', String(data.playerId))
    localStorage.setItem('playerName', data.playerName)
    localStorage.setItem('sex', data.sex)
  }

  function logout() {
    token.value = ''
    userId.value = 0
    username.value = ''
    playerId.value = 0
    playerName.value = ''
    localStorage.removeItem('token')
    localStorage.removeItem('userId')
    localStorage.removeItem('username')
    localStorage.removeItem('playerId')
    localStorage.removeItem('playerName')
    localStorage.removeItem('sex')
    router.push('/')
  }

  return {
    token,
    userId,
    username,
    playerId,
    playerName,
    sex,
    isAuthenticated,
    login,
    register,
    changePassword,
    logout
  }
})
