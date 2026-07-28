import SockJS from 'sockjs-client'
import { Client } from '@stomp/stompjs'

interface Callbacks {
  onMessage?: (msg: any) => void
  onConnect?: () => void
  onDisconnect?: () => void
  onError?: (error: any) => void
}

class GameWebSocket {
  private stompClient: Client | null = null
  private connected = false
  private callbacks: Callbacks = {}
  private reconnectTimer: any = null
  private subscriptions: any[] = []

  connect(token: string, callbacks: Callbacks) {
    this.callbacks = callbacks

    const socket = new SockJS('/ws?token=' + encodeURIComponent(token))

    this.stompClient = new Client({
      webSocketFactory: () => socket as any,
      connectHeaders: {
        Authorization: `Bearer ${token}`
      },
      onConnect: (frame) => {
        console.log('WebSocket连接成功:', frame)
        this.connected = true
        this.callbacks.onConnect?.()
      },
      onDisconnect: () => {
        console.log('WebSocket断开连接')
        this.connected = false
        this.callbacks.onDisconnect?.()
        this.scheduleReconnect(token)
      },
      onStompError: (frame) => {
        console.error('STOMP错误:', frame)
        this.callbacks.onError?.(frame)
      }
    })

    this.stompClient.activate()
  }

  private scheduleReconnect(token: string) {
    if (this.reconnectTimer) {
      clearTimeout(this.reconnectTimer)
    }
    this.reconnectTimer = setTimeout(() => {
      console.log('尝试重新连接...')
      this.subscriptions = []
      this.connect(token, this.callbacks)
    }, 5000)
  }

  disconnect() {
    if (this.reconnectTimer) {
      clearTimeout(this.reconnectTimer)
      this.reconnectTimer = null
    }
    this.subscriptions.forEach(sub => {
      try { sub.unsubscribe() } catch (e) { /* ignore */ }
    })
    this.subscriptions = []
    if (this.stompClient && this.connected) {
      this.stompClient.deactivate()
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
      this.stompClient.publish({
        destination: '/app/command',
        body: JSON.stringify({ command })
      })
    } else {
      console.warn('WebSocket未连接，无法发送命令')
    }
  }

  /**
   * 订阅玩家私人消息
   */
  subscribePlayer(playerId: number) {
    if (this.stompClient && this.connected) {
      // 订阅私人消息 - Spring自动根据会话匹配，不需要在路径中指定userId
      const sub1 = this.stompClient.subscribe('/user/queue/messages', (message: any) => {
        console.log('[WS收到消息]', message.body)
        const msg = JSON.parse(message.body)
        this.callbacks.onMessage?.(msg)
      })
      this.subscriptions.push(sub1)

      // 订阅系统消息
      const sub2 = this.stompClient.subscribe('/topic/system', (message: any) => {
        console.log('[WS收到系统消息]', message.body)
        const msg = JSON.parse(message.body)
        this.callbacks.onMessage?.(msg)
      })
      this.subscriptions.push(sub2)
    }
  }

  /**
   * 订阅房间消息
   */
  subscribeRoom(roomId: number) {
    if (this.stompClient && this.connected) {
      const sub = this.stompClient.subscribe(`/topic/room/${roomId}`, (message: any) => {
        const msg = JSON.parse(message.body)
        this.callbacks.onMessage?.(msg)
      })
      this.subscriptions.push(sub)
    }
  }

  /**
   * 订阅聊天频道
   */
  subscribeChatChannel(channel: string) {
    if (this.stompClient && this.connected) {
      const sub = this.stompClient.subscribe(`/topic/chat/${channel}`, (message: any) => {
        const msg = JSON.parse(message.body)
        this.callbacks.onMessage?.(msg)
      })
      this.subscriptions.push(sub)
    }
  }
}

export const gameWebSocket = new GameWebSocket()
export default gameWebSocket
