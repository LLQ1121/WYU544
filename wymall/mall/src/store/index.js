import Vue from 'vue'
import Vuex from 'vuex'
import axios from 'axios'
import api from "../assets/config/api.js";

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    cartTotal: {
      checkedGoodsAmount: 0,
      checkedGoodsCount: 0,
      goodsAmount: 0,
      goodsCount: 0
    },
    cartList: [],
  },
  mutations: {
    setCartList:function(state,carList){
      state.cartList = carList
    },
    setCartTotal:function(state,cartTotal){
      state.cartTotal = cartTotal
    }
  },
  actions: {
    AjaxCart: async function(content){
      let carRes = await axios.get(api.CartList)
      content.commit('setCartList',carRes.data.data.cartList)
      content.commit('setCartTotal',carRes.data.data.cartTotal)
    }
  },
  modules: {
  }
})
