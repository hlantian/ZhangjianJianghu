<template>
  <div class="login-container">
    <div class="login-box">
      <h1>密码修改</h1>
      <input v-model="username" type="text" placeholder="用户名" />
      <input v-model="oldPassword" type="password" placeholder="旧密码" />
      <input v-model="newPassword" type="password" placeholder="新密码(6-30字符)" />
      <button @click="handleChange" :disabled="loading">
        {{ loading ? '修改中...' : '修改密码' }}
      </button>
      <p style="margin-top: 15px;">
        <router-link to="/" style="color: #FFD700;">返回</router-link>
      </p>
      <p v-if="errorMsg" style="color: #FF6666; margin-top: 10px;">{{ errorMsg }}</p>
      <p v-if="successMsg" style="color: #66FF66; margin-top: 10px;">{{ successMsg }}</p>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'
import { useAuthStore } from '@/stores/auth'

const authStore = useAuthStore()

const username = ref('')
const oldPassword = ref('')
const newPassword = ref('')
const loading = ref(false)
const errorMsg = ref('')
const successMsg = ref('')

async function handleChange() {
  if (!username.value || !oldPassword.value || !newPassword.value) {
    errorMsg.value = '请填写所有字段'
    return
  }
  if (newPassword.value.length < 6) {
    errorMsg.value = '新密码至少6位'
    return
  }

  loading.value = true
  errorMsg.value = ''
  successMsg.value = ''

  try {
    await authStore.changePassword({
      username: username.value,
      oldPassword: oldPassword.value,
      newPassword: newPassword.value
    })
    successMsg.value = '密码修改成功！'
    oldPassword.value = ''
    newPassword.value = ''
  } catch (e: any) {
    errorMsg.value = e.message || '修改失败'
  } finally {
    loading.value = false
  }
}
</script>
