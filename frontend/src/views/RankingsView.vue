<template>
  <div class="login-container">
    <div class="login-box" style="width: 500px;">
      <h1>江湖风云榜</h1>
      <div style="display: flex; gap: 20px; margin: 15px 0;">
        <button @click="tab = 'exp'" :style="tab === 'exp' ? 'background: #1874CD' : ''">经验排行</button>
        <button @click="tab = 'money'" :style="tab === 'money' ? 'background: #1874CD' : ''">财富排行</button>
      </div>
      <table style="width: 100%; font-size: 12px; color: #fff; border-collapse: collapse;">
        <thead>
          <tr style="border-bottom: 1px solid #555;">
            <th style="padding: 5px; text-align: center;">排名</th>
            <th style="padding: 5px; text-align: center;">角色名</th>
            <th style="padding: 5px; text-align: center;">{{ tab === 'exp' ? '经验' : '存款' }}</th>
            <th v-if="tab === 'exp'" style="padding: 5px; text-align: center;">等级</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="item in rankings" :key="item.rank" style="border-bottom: 1px solid #333;">
            <td style="padding: 5px; text-align: center;">{{ item.rank }}</td>
            <td style="padding: 5px; text-align: center;">{{ item.name }}</td>
            <td style="padding: 5px; text-align: center;">{{ tab === 'exp' ? item.experience : item.deposit }}</td>
            <td v-if="tab === 'exp'" style="padding: 5px; text-align: center;">{{ item.level }}</td>
          </tr>
        </tbody>
      </table>
      <p v-if="rankings.length === 0" style="text-align: center; padding: 20px;">暂无数据</p>
      <p style="margin-top: 15px;">
        <router-link to="/" style="color: #FFD700;">返回</router-link>
      </p>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, watch, onMounted } from 'vue'
import api from '@/api'

const tab = ref('exp')
const rankings = ref<any[]>([])

async function fetchRankings() {
  try {
    const res: any = await api.get(`/public/rankings/${tab.value}`)
    rankings.value = res.data || []
  } catch (e) {
    rankings.value = []
  }
}

watch(tab, fetchRankings)
onMounted(fetchRankings)
</script>
