<template>
  <div class="login-container">
    <div class="login-box">
      <h1>仗剑江湖</h1>
      <p style="margin-bottom: 15px;">目前在线 ({{ onlineCount }}) 人</p>
      <input
        v-model="username"
        type="text"
        placeholder="代号"
        @keydown.enter="handleLogin"
      />
      <input
        v-model="password"
        type="password"
        placeholder="密码"
        @keydown.enter="handleLogin"
      />
      <button @click="handleLogin" :disabled="loading">
        {{ loading ? '登录中...' : '进入' }}
      </button>
      <p style="margin-top: 15px;">
        <router-link to="/register" style="color: #FFD700;">注册江湖</router-link>
        &nbsp;|&nbsp;
        <router-link to="/rankings" style="color: #FFD700;">江湖风云榜</router-link>
        &nbsp;|&nbsp;
        <router-link to="/password" style="color: #FFD700;">密码修改</router-link>
      </p>
      <p v-if="errorMsg" style="color: #FF6666; margin-top: 10px;">{{ errorMsg }}</p>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from 'vue'
import { useRouter } from 'vue-router'
import { useAuthStore } from '@/stores/auth'
import api from '@/api'

const router = useRouter()
const authStore = useAuthStore()

const username = ref('')
const password = ref('')
const loading = ref(false)
const errorMsg = ref('')
const onlineCount = ref(0)

async function fetchOnlineCount() {
  try {
    const res: any = await api.get('/public/online-count')
    onlineCount.value = res.data || 0
  } catch (e) {
    // 忽略
  }
}

async function handleLogin() {
  if (!username.value || !password.value) {
    errorMsg.value = '请填写用户名和密码'
    return
  }

  loading.value = true
  errorMsg.value = ''

  try {
    await authStore.login({
      username: username.value,
      password: password.value
    })
    router.push('/game')
  } catch (e: any) {
    errorMsg.value = e.message || '登录失败'
  } finally {
    loading.value = false
  }
}

onMounted(() => {
  fetchOnlineCount()
  setInterval(fetchOnlineCount, 30000)
})
</script>
