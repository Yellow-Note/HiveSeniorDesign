/* eslint-disable */
import { createRouter, createWebHashHistory } from 'vue-router'

const routes = [
  {
    path: "/",
    name: "home",
    component: () => import("../views/Home-View.vue"),
  },
  {
    path: "/about",
    name: "getting-started-view",
    component: () => import("../views/About-View.vue"),
  },
  {
    path: "/queue-view",
    name: "queue-view",
    component: () => import("../views/Queue-View.vue"),
  },
  {
    path: "/GPSMap-view",
    name: "GPSMap-view",
    component: () => import("../views/GPSMap-View.vue"),
  },
  {
    path: "/tutorial-view",
    name: "tutorial-view",
    component: () => import("../views/Tutorial-View.vue"),
  },
];

const router = createRouter({
  history: createWebHashHistory(),
  routes
})

export default router
