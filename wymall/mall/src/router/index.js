import Vue from 'vue'
import VueRouter from 'vue-router'
import Home from '../views/Home.vue'
import category from '../views/category.vue'
import categoryList from '../views/categoryList.vue'
import product from '../views/product.vue'
import buycart from '../views/buycart.vue'
import topic from '../views/topic.vue'
import my from '../views/my.vue'

Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    name: 'home',
    component: Home
  },
  {
    path: '/about',
    name: 'about',
    // route level code-splitting
    // this generates a separate chunk (about.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
    component: () => import(/* webpackChunkName: "about" */ '../views/About.vue')
  },
  {
    path: '/category',
    name: 'category',
    component: category
  },
  {
    path:'/categoryList/:id',
    name:'categoryList',
    component:categoryList,
    props:true
  },
  {
    path:'/product/:id',
    name:'product',
    component:product,
    props:true
  },
  {
    path: '/buycart',
    name: 'buycart',
    component: buycart
  },
  {
    path: '/topic',
    name: 'topic',
    component: topic
  },
  {
    path: '/my',
    name: 'my',
    component: my
  }
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
