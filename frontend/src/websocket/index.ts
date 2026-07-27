import SockJS from 'sockjs-client'
import Stomp from 'stomp-websocket'
import { useAuthStore } from '@/stores/auth'

interface Callbacks {
  onMessage?: (msg: any) => void
  onConnect?: () => void
  onDisconnect?: () => void
  onError?: (error: any) => void
}

class GameWebSocket {
  private stompClient: any = null
  private connected = false
  private callbacks: Callbacks = {}
  private reconnectTimer: any = null

  connect(token: string, callbacks: Callbacks) {
    this.callbacks = callbacks

    const socket = new SockJS('/ws')
    this.stompClient = Stomp.over(socket)

    this.stompClient.connect(
      { Authorization: `Bearer ${token}` },
      (frame: any) => {
        console.log('WebSocket连接成功:', frame)
        this.connected = true
        this.callbacks.onConnect?.()
      },
      (error: any) => {
        console.error('WebSocket连接失败:', error)
        this.connected = false
        this.callbacks.onDisconnect?.()
        // 自动重连
        this.scheduleReconnect(token)
      }
    )
  }

  private scheduleReconnect(token: string) {
    if (this.reconnectTimer) {
      clearTimeout(this.reconnectTimer)
    }
    this.reconnectTimer = setTimeout(() => {
      console.log('尝试重新连接...')
      this.connect(token, this.callbacks)
    }, 5000)
  }

  disconnect() {
    if (this.reconnectTimer) {
      clearTimeout(this.reconnectTimer)
      this.reconnectTimer = null
    }
    if (this.stompClient && this.connected) {
      this.stompClient.disconnect(() => {
        console.log('WebSocket已断开')
      })
    }
    this.connected = false
  }

  isConnected() {
    return this.connected
  }

  /**
   * 发送游戏命令
   */
  sendCommand(command: string) {
    if (this.stompClient && this.connected) {
      this.stompClient.send('/app/command', {}, JSON.stringify({ command }))
    } else {
      console.warn('WebSocket未连接，无法发送命令')
    }
  }

  /**
   * 订阅玩家私人消息
   */
  subscribePlayer(playerId: number) {
    if (this.stompClient && this.connected) {
      this.stompClient.subscribe(`/user/${playerId}/queue/messages`, (message: any) => {
        const msg = JSON.parse(message.body)
        this.callbacks.onMessage?.(msg)
      })

      // 订阅系统消息
      this.stompClient.subscribe('/topic/system', (message: any) => {
        const msg = JSON.parse(message.body)
        this.callbacks.onMessage?.(msg)
      })
    }
  }

  /**
   * 订阅房间消息
   */
  subscribeRoom(roomId: number) {
    if (this.stompClient && this.connected) {
      this.stompClient.subscribe(`/topic/room/${roomId}`, (message: any) => {
        const msg = JSON.parse(message.body)
        this.callbacks.onMessage?.(msg)
      })
    }
  }

  /**
   * 订阅聊天频道
   */
  subscribeChatChannel(channel: string) {
    if (this.stompClient && this.connected) {
      this.stompClient.subscribe(`/topic/chat/${channel}`, (message: any) => {
        const msg = JSON.parse(message.body)
        this.callbacks.onMessage?.(msg)
      })
    }
  }

  /**
   * 取消订阅房间
   */
  unsubscribeRoom(roomId: number) {
    // STOMP的subscription可以保存引用后unsubscribe
    // 简化实现: 重新订阅时会覆盖
  }
}

export const gameWebSocket = new GameWebSocket()
export default gameWebSocket
