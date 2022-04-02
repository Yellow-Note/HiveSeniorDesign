import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'
var datapoints = [
        {
          imageLocation: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture1.jpg',
          imageName: 'Pin 1 Timestamp 00:00:00',
          lat: 41.15467,
          lng: -105.3733
        },
        {
          imageLocation: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture2.jpg',
          imageName: 'Pin 2 Timestamp 12:34:15',
          lat: 41.1544,
          lng: -105.3745
        },
        {
          imageLocation: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture3.jpg',
          imageName: 'Pin 3 Timestamp 15:14:33',
          lat: 41.1585,
          lng: -105.370
        },
      ]

const routes = [
  {
    path: '/',
    name: 'home',
    component: HomeView
  },
  {
    path: '/getting-started',
    name: 'getting-started',
    // route level code-splitting
    // this generates a separate chunk (about.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
    component: () => import(/* webpackChunkName: "about" */ '../views/GettingStarted.vue')
  },
  {
    path: '/queue',
    name: 'queue',
    // route level code-splitting
    // this generates a separate chunk (about.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
    component: () => import(/* webpackChunkName: "about" */ '../views/QueueView.vue')
  },
  {
    path: '/gps',
    name: 'gps',
    // route level code-splitting
    // this generates a separate chunk (about.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
    component: () => import(/* webpackChunkName: "about" */ '../views/GPSView.vue'),
    props: {datapoints: datapoints}
  }
  ,
  {
    path: '/tutorial',
    name: 'tutorial',
    // route level code-splitting
    // this generates a separate chunk (about.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
    component: () => import(/* webpackChunkName: "about" */ '../views/TutorialView.vue')
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

export default router
