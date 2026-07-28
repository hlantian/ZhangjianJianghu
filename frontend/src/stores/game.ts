import { defineStore } from 'pinia'
import { ref } from 'vue'
import { useAuthStore } from './auth'
import { gameWebSocket } from '@/websocket'

export interface GameActor {
  name: string
  displayName: string
  x: number
  y: number
  pic?: number
}

export interface ChatMessage {
  channel: string
  sender: string
  message: string
  timestamp: Date
}

export const useGameStore = defineStore('game', () => {
  const authStore = useAuthStore()

  // 连接状态
  const connected = ref(false)
  const onlineCount = ref(0)

  // 房间信息
  const roomId = ref<number>(0)
  const roomName = ref('')
  const roomDescription = ref('')

  // 房间内人物
  const actors = ref<GameActor[]>([])

  // 玩家状态
  const body = ref(100)
  const maxBody = ref(100)
  const energy = ref(100)
  const maxEnergy = ref(100)
  const internalForce = ref(0)
  const maxInternalForce = ref(0)
  const food = ref(150)
  const maxFood = ref(200)
  const drink = ref(150)
  const maxDrink = ref(200)

  // 聊天消息
  const messages = ref<ChatMessage[]>([])
  const chatMessages = ref<ChatMessage[]>([])

  // 战斗状态
  const inCombat = ref(false)
  const adversary = ref('')

  function connect() {
    gameWebSocket.connect(authStore.token, {
      onMessage: handleMessage,
      onConnect: () => {
        connected.value = true
        gameWebSocket.subscribePlayer(authStore.userId)
      },
      onDisconnect: () => {
        connected.value = false
      }
    })
  }

  function disconnect() {
    gameWebSocket.disconnect()
    connected.value = false
  }

  function sendCommand(command: string) {
    gameWebSocket.sendCommand(command)
  }

  function handleMessage(msg: any) {
    const { type, content, actorName, actorDisplayName, x, y } = msg

    switch (type) {
      case 'INFO':
      case 'SYSTEM':
      case 'ERROR':
      case 'ROOM':
      case 'COMBAT':
        messages.value.push({
          channel: type,
          sender: actorName || '',
          message: content || '',
          timestamp: new Date()
        })
        // 限制消息数量
        if (messages.value.length > 200) {
          messages.value.shift()
        }
        break

      case 'CHAT':
        chatMessages.value.push({
          channel: 'chat',
          sender: actorName || '',
          message: content || '',
          timestamp: new Date()
        })
        if (chatMessages.value.length > 200) {
          chatMessages.value.shift()
        }
        break

      case 'HP_UPDATE':
        if (content) {
          const parts = content.split(',')
          if (parts.length >= 10) {
            body.value = Number(parts[0])
            maxBody.value = Number(parts[1])
            energy.value = Number(parts[2])
            maxEnergy.value = Number(parts[3])
            internalForce.value = Number(parts[4])
            maxInternalForce.value = Number(parts[5])
            food.value = Number(parts[6])
            maxFood.value = Number(parts[7])
            drink.value = Number(parts[8])
            maxDrink.value = Number(parts[9])
          }
        }
        break

      case 'ACTOR_ENTER':
        // 避免重复添加
        if (!actors.value.find(a => a.name === actorName)) {
          actors.value.push({
            name: actorName,
            displayName: actorDisplayName || actorName,
            x: x || 50,
            y: y || 50
          })
        }
        break

      case 'CLEAR_ACTORS':
        actors.value = []
        break

      case 'ACTOR_LEAVE':
        actors.value = actors.value.filter(a => a.name !== actorName)
        break

      case 'ACTOR_MOVE':
        const actor = actors.value.find(a => a.name === actorName)
        if (actor) {
          actor.x = x
          actor.y = y
        }
        break

      case 'ACTOR_SAY':
        messages.value.push({
          channel: 'say',
          sender: actorName || '',
          message: content || '',
          timestamp: new Date()
        })
        break

      case 'ACTOR_DIE':
        const deadActor = actors.value.find(a => a.name === actorName)
        if (deadActor) {
          actors.value = actors.value.filter(a => a.name !== actorName)
        }
        break

      case 'ROOM_INFO':
        if (content) {
          roomName.value = content
        }
        break
    }
  }

  function clearMessages() {
    messages.value = []
  }

  return {
    connected,
    onlineCount,
    roomId,
    roomName,
    roomDescription,
    actors,
    body,
    maxBody,
    energy,
    maxEnergy,
    internalForce,
    maxInternalForce,
    food,
    maxFood,
    drink,
    maxDrink,
    messages,
    chatMessages,
    inCombat,
    adversary,
    connect,
    disconnect,
    sendCommand,
    clearMessages,
    handleMessage
  }
})
