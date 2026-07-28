<template>
  <div class="game-container">
    <!-- 顶部导航 -->
    <div class="game-header">
      <span class="game-header-title">仗剑江湖</span>
      <div class="game-header-actions">
        <a @click="sendCmd('who')">在线名单</a>
        <a @click="sendCmd('hp')">体力</a>
        <a @click="sendCmd('score')">状态</a>
        <a @click="sendCmd('inventory')">物品</a>
        <a @click="sendCmd('skills')">武功</a>
        <a @click="goRankings">排行榜</a>
        <a @click="handleQuit">退出</a>
      </div>
    </div>

    <div class="game-main">
      <!-- 左侧: 房间描述 + 游戏画面 + 命令输入 + 快捷按钮 -->
      <div class="game-left">
        <!-- 房间描述 -->
        <div class="room-description" ref="roomDescRef">
          <b>{{ gameStore.roomName || '游戏世界' }}</b><br>
          <div v-html="formattedRoomDescription"></div>
        </div>

        <!-- 游戏画面 -->
        <div class="game-canvas" @click="handleCanvasClick">
          <div
            v-for="actor in gameStore.actors"
            :key="actor.name"
            class="actor-sprite"
            :style="{
              left: actor.x + 'px',
              top: actor.y + 'px',
              position: 'absolute'
            }"
          >
            <div style="text-align: center;">
              <div style="font-size: 11px; color: #003300; margin-bottom: 2px;">{{ actor.displayName }}</div>
              <div class="actor-avatar" :style="{ background: getActorColor(actor) }">
                {{ getActorEmoji(actor) }}
              </div>
            </div>
          </div>
        </div>

        <!-- 命令输入 -->
        <div class="command-input">
          <select v-model="selectedChannel">
            <option value="">命令</option>
            <option value="say">说话</option>
            <option value="chat">公用频道</option>
            <option value="rumor">谣言频道</option>
            <option value="newbie">新手频道</option>
            <option value="party">门派频道</option>
          </select>
          <input
            v-model="commandText"
            type="text"
            placeholder="输入命令或消息..."
            @keydown.enter="sendCommand"
            @keydown.up="historyUp"
            @keydown.down="historyDown"
            ref="inputRef"
          />
          <button @click="sendCommand">发送</button>
        </div>

        <!-- 快捷按钮 -->
        <div class="quick-buttons">
          <button v-for="(btn, i) in quickButtons" :key="i" @click="sendCmd(btn.cmd)">
            {{ btn.label }}
          </button>
        </div>
      </div>

      <!-- 右侧: 状态面板 + 信息窗口 -->
      <div class="game-right">
        <!-- 状态面板 -->
        <div class="status-panel">
          <div class="hp-bar">
            <span class="hp-bar-label">气血</span>
            <div class="hp-bar-track">
              <div class="hp-bar-fill" :style="{ width: hpPercent + '%', backgroundColor: '#FF4444' }"></div>
            </div>
            <span class="hp-bar-text">{{ gameStore.body }}/{{ gameStore.maxBody }}</span>
          </div>
          <div class="hp-bar">
            <span class="hp-bar-label">精力</span>
            <div class="hp-bar-track">
              <div class="hp-bar-fill" :style="{ width: energyPercent + '%', backgroundColor: '#44AA44' }"></div>
            </div>
            <span class="hp-bar-text">{{ gameStore.energy }}/{{ gameStore.maxEnergy }}</span>
          </div>
          <div class="hp-bar">
            <span class="hp-bar-label">内力</span>
            <div class="hp-bar-track">
              <div class="hp-bar-fill" :style="{ width: forcePercent + '%', backgroundColor: '#4488FF' }"></div>
            </div>
            <span class="hp-bar-text">{{ gameStore.internalForce }}/{{ gameStore.maxInternalForce }}</span>
          </div>
          <div class="hp-bar">
            <span class="hp-bar-label">食物</span>
            <div class="hp-bar-track">
              <div class="hp-bar-fill" :style="{ width: foodPercent + '%', backgroundColor: '#AA8800' }"></div>
            </div>
            <span class="hp-bar-text">{{ gameStore.food }}/{{ gameStore.maxFood }}</span>
          </div>
          <div class="hp-bar">
            <span class="hp-bar-label">饮水</span>
            <div class="hp-bar-track">
              <div class="hp-bar-fill" :style="{ width: drinkPercent + '%', backgroundColor: '#44AAAA' }"></div>
            </div>
            <span class="hp-bar-text">{{ gameStore.drink }}/{{ gameStore.maxDrink }}</span>
          </div>
        </div>

        <!-- 信息窗口 -->
        <div class="message-window" ref="messageWindowRef">
          <div
            v-for="(msg, i) in gameStore.messages"
            :key="i"
            :class="'message-' + (msg.channel || '').toLowerCase()"
            class="message-line"
            v-html="formatMessage(msg)"
          ></div>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted, onUnmounted, nextTick, watch } from 'vue'
import { useRouter } from 'vue-router'
import { useAuthStore } from '@/stores/auth'
import { useGameStore } from '@/stores/game'

const router = useRouter()
const authStore = useAuthStore()
const gameStore = useGameStore()

const commandText = ref('')
const selectedChannel = ref('')
const inputRef = ref<HTMLInputElement | null>(null)
const messageWindowRef = ref<HTMLDivElement | null>(null)
const roomDescRef = ref<HTMLDivElement | null>(null)

const history = ref<string[]>([])
const historyIndex = ref(-1)

const quickButtons = ref([
  { label: '我闪', cmd: '我闪' },
  { label: '任务', cmd: 'quest' },
  { label: '放弃', cmd: 'giveup' },
  { label: '补血', cmd: 'yun qi' },
  { label: '精力', cmd: 'yun jing' },
  { label: '查看', cmd: 'look' },
  { label: '状态', cmd: 'score' },
  { label: '武功', cmd: 'skills' },
  { label: '物品', cmd: 'i' },
  { label: '帮助', cmd: 'help' }
])

const hpPercent = computed(() => {
  return gameStore.maxBody > 0 ? (gameStore.body / gameStore.maxBody) * 100 : 0
})

const energyPercent = computed(() => {
  return gameStore.maxEnergy > 0 ? (gameStore.energy / gameStore.maxEnergy) * 100 : 0
})

const forcePercent = computed(() => {
  return gameStore.maxInternalForce > 0 ? (gameStore.internalForce / gameStore.maxInternalForce) * 100 : 0
})

const foodPercent = computed(() => {
  return gameStore.maxFood > 0 ? (gameStore.food / gameStore.maxFood) * 100 : 0
})

const drinkPercent = computed(() => {
  return gameStore.maxDrink > 0 ? (gameStore.drink / gameStore.maxDrink) * 100 : 0
})

const formattedRoomDescription = computed(() => {
  return (gameStore.roomDescription || '欢迎来到仗剑江湖！').replace(/\n/g, '<br>')
})

function sendCommand() {
  const cmd = commandText.value.trim()
  if (!cmd) return

  // 记录历史
  history.value.push(cmd)
  if (history.value.length > 50) {
    history.value.shift()
  }
  historyIndex.value = -1

  // 根据频道选择处理
  if (selectedChannel.value && selectedChannel.value !== '命令') {
    gameStore.sendCommand(`${selectedChannel.value} ${cmd}`)
  } else {
    gameStore.sendCommand(cmd)
  }

  commandText.value = ''
  selectedChannel.value = ''
}

function sendCmd(cmd: string) {
  gameStore.sendCommand(cmd)
}

function historyUp() {
  if (history.value.length === 0) return
  if (historyIndex.value === -1) {
    historyIndex.value = history.value.length - 1
  } else if (historyIndex.value > 0) {
    historyIndex.value--
  }
  commandText.value = history.value[historyIndex.value]
}

function historyDown() {
  if (historyIndex.value === -1) return
  if (historyIndex.value < history.value.length - 1) {
    historyIndex.value++
    commandText.value = history.value[historyIndex.value]
  } else {
    historyIndex.value = -1
    commandText.value = ''
  }
}

function handleCanvasClick(event: MouseEvent) {
  const rect = (event.currentTarget as HTMLElement).getBoundingClientRect()
  const x = Math.floor(event.clientX - rect.left)
  const y = Math.floor(event.clientY - rect.top)
  gameStore.sendCommand(`move ${x} ${y}`)
}

function getActorColor(actor: any) {
  // 根据名称hash生成颜色
  const colors = ['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4', '#FFEAA7', '#DDA0DD', '#98D8C8', '#F7DC6F']
  const hash = (actor.name || '').charCodeAt(0) % colors.length
  return colors[hash]
}

function getActorEmoji(actor: any) {
  // 名字带"(你)"的是玩家自己
  if (actor.displayName && actor.displayName.includes('(你)')) {
    return '🧑'
  }
  // 名字不带"(你)"的可能是其他玩家或NPC
  // 简单区分：名字长度<=2且不含称号的可能是NPC
  return '🧑'
}

function formatMessage(msg: any) {
  let text = msg.message || ''
  if (msg.sender) {
    return `<b>【${msg.sender}】</b>${text}`
  }
  return text
}

function goRankings() {
  router.push('/rankings')
}

function handleQuit() {
  gameStore.sendCommand('quit')
  setTimeout(() => {
    gameStore.disconnect()
    authStore.logout()
  }, 500)
}

// 自动滚动到底部
watch(() => gameStore.messages.length, async () => {
  await nextTick()
  if (messageWindowRef.value) {
    messageWindowRef.value.scrollTop = messageWindowRef.value.scrollHeight
  }
})

onMounted(() => {
  // 连接WebSocket
  gameStore.connect()
  // 发送look命令获取初始信息
  setTimeout(() => {
    gameStore.sendCommand('look')
  }, 1000)
})

onUnmounted(() => {
  gameStore.disconnect()
})
</script>

<style scoped>
.actor-sprite {
  transition: all 0.3s ease;
  z-index: 5;
}
.actor-avatar {
  width: 38px;
  height: 38px;
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 18px;
  border: 2px solid #333;
  box-shadow: 0 2px 4px rgba(0,0,0,0.3);
}
</style>
