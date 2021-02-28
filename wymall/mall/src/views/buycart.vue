<template>
  <div id="buycart">
    <div class="info">
      <span>30天无忧退货</span>
      <span>48小时极速退款</span>
      <span>满88免邮费</span>
    </div>
    <!-- 商品列表 -->
    <div class="list">
      <div class="carItem" v-for="(item, index) in cartList" :key="index">
        <van-checkbox
          @change="checkEvent($event, item)"
          v-model="item.checked"
        ></van-checkbox>
        <van-image width="70" height="70" :src="item.list_pic_url" />
        <div class="proBrief">
          <div class="title">
            <span>{{ item.goods_name }}</span>
            <span class="num">×{{ item.number }}</span>
          </div>
          <p class="brief">{{ item.goods_specifition_name_value }}</p>
          <p class="price">￥ {{ item.retail_price }}</p>
        </div>
      </div>
    </div>
    <!-- 商品全选 -->
    <van-submit-bar 
      :price="cartTotal.checkedGoodsAmount * 100"
      button-text="提交订单"
      @submit="onSubmit"
    >
        <van-checkbox v-model="checkedAll">全选</van-checkbox>
    </van-submit-bar>

    <div style="height:50px"></div>
    <tab-button></tab-button>
  </div>
</template>

<script>
import axios from 'axios'
import { mapState } from "vuex";
import api from "../assets/config/api.js";
import tabButton from "../components/tabButton.vue";
let mapStateObj = mapState(["cartTotal", "cartList"]);
export default {
  data() {
    return {
      checked: true
    };
  },
  computed: {
    ...mapStateObj,
    checkedAll:{
        set(val){
            
        },
        get(){
            if(this.cartTotal.goodsCount==this.cartTotal.checkedGoodsCount){
                return true;
            }else{
                return false
            }
        }
    }
  },
  components:{
      tabButton
  },
  created() {
    this.$store.dispatch("AjaxCart");
  },
  mounted() {
    // console.log(this.cartList);
    // console.log(this.cartTotal);
  },
  methods: {
    onSubmit: function () {
    },
    checkEvent:async function(event,item){
        let res = await axios.post(api.CartChecked,{isChecked: Number(event),productIds: item.product_id})
        let data = res.data.data
        this.$store.commit('setCartList',data.cartList),
        this.$store.commit('setCartTotal',data.cartTotal)
        this.$forceUpdate()
    }, 
  },
};
</script>

<style lang="less">
#buycart {
  .info {
    display: flex;
    justify-content: space-around;
    font-size: 12px;
    color: #999;
    height: 24px;
    line-height: 24px;
    background: #efefee;
    span {
      position: relative;
    }
    span::before {
      content: "";
      display: block;
      position: absolute;
      left: -10px;
      top: 8px;
      width: 4px;
      height: 4px;
      border-radius: 2px;
      border: 1px solid red;
    }
  }
  .carItem {
    padding: 0 5px;
    display: flex;
    align-items: center;
    padding: 10px 5px;
    .van-checkbox {
      margin: 0 5px;
    }
    .van-image {
      background: #efefef;
    }
    .proBrief {
      flex: 1;
      display: flex;
      flex-direction: column;
      justify-content: space-around;
      align-items: flex-start;
      .title {
        width: 100%;
        font-size: 14px;
        display: flex;
        justify-content: space-between;
      }
      .brief {
        color: #999;
        font-size: 12px;
      }
    }
  }
  .van-submit-bar{
      bottom:51px;
  }
}
</style>