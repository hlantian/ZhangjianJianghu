<template>
  <div class="login-container">
    <div class="login-box">
      <h1>注册江湖</h1>
      <input v-model="username" type="text" placeholder="用户名(2-20字符)" />
      <input v-model="password" type="password" placeholder="密码(6-30字符)" />
      <div style="margin: 8px 0;">
        <label style="font-size: 12px;">性别：</label>
        <label style="font-size: 12px; margin-left: 10px;">
          <input type="radio" value="m" v-model="sex" /> 男
        </label>
        <label style="font-size: 12px; margin-left: 10px;">
          <input type="radio" value="f" v-model="sex" /> 女
        </label>
      </div>
      <input v-model="playerName" type="text" placeholder="角色名(2-10字符)" />
      <button @click="handleRegister" :disabled="loading">
        {{ loading ? '注册中...' : '注册' }}
      </button>
      <p style="margin-top: 15px;">
        <router-link to="/" style="color: #FFD700;">返回登录</router-link>
      </p>
      <p v-if="errorMsg" style="color: #FF6666; margin-top: 10px;">{{ errorMsg }}</p>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'
import { useRouter } from 'vue-router'
import { useAuthStore } from '@/stores/auth'

const router = useRouter()
const authStore = useAuthStore()

const username = ref('')
const password = ref('')
const sex = ref('m')
const playerName = ref('')
const loading = ref(false)
const errorMsg = ref('')

async function handleRegister() {
  if (!username.value || !password.value || !playerName.value) {
    errorMsg.value = '请填写所有字段'
    return
  }
  if (password.value.length < 6) {
    errorMsg.value = '密码至少6位'
    return
  }
  if (playerName.value.length < 2) {
    errorMsg.value = '角色名至少2个字符'
    return
  }

  loading.value = true
  errorMsg.value = ''

  try {
    await authStore.register({
      username: username.value,
      password: password.value,
      sex: sex.value,
      playerName: playerName.value
    })
    router.push('/game')
  } catch (e: any) {
    errorMsg.value = e.message || '注册失败'
  } finally {
    loading.value = false
  }
}
</script>
