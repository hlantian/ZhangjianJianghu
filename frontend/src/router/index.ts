import { createRouter, createWebHistory } from 'vue-router'
import { useAuthStore } from '@/stores/auth'

const router = createRouter({
  history: createWebHistory(),
  routes: [
    {
      path: '/',
      name: 'home',
      component: () => import('@/views/LoginView.vue')
    },
    {
      path: '/register',
      name: 'register',
      component: () => import('@/views/RegisterView.vue')
    },
    {
      path: '/game',
      name: 'game',
      component: () => import('@/views/GameView.vue'),
      meta: { requiresAuth: true }
    },
    {
      path: '/rankings',
      name: 'rankings',
      component: () => import('@/views/RankingsView.vue')
    },
    {
      path: '/password',
      name: 'password',
      component: () => import('@/views/PasswordView.vue')
    }
  ]
})

router.beforeEach((to, _from, next) => {
  const authStore = useAuthStore()
  if (to.meta.requiresAuth && !authStore.isAuthenticated) {
    next({ name: 'home' })
  } else if (to.name === 'home' && authStore.isAuthenticated) {
    next({ name: 'game' })
  } else {
    next()
  }
})

export default router
