<template>
  <div class="home">
    <van-search v-model="searchData" input-align="center" placeholder="请输入搜索关键词" />
    <van-swipe :autoplay="3000" :width="375" :height="200">
      <van-swipe-item v-for="(image, index) in images" :key="index">
      <img id="swipeImage" v-lazy="image.image_url" />
      </van-swipe-item>
    </van-swipe>

    <!-- 宫格 -->
    <van-grid :column-num="5">
      <van-grid-item v-for="(item,index) in channels" :key="index" :icon="item.icon_url" :text="item.name" />
    </van-grid>
    <!-- 面板 品牌制造商直供 -->
    <van-panel title="品牌制造商直供">
      <div class="brand">
        <van-grid :border="false" :column-num="2">
          <van-grid-item v-for="(itemBrand,indexBrand) in brandList" :key="indexBrand">
            <van-image width="100%" height="100%" lazy-load :src="itemBrand.new_pic_url" />
            <h4 class="title">{{itemBrand.name}}</h4>
            <p class="price">{{itemBrand.floor_price}}元起</p>
          </van-grid-item>
        </van-grid>
      </div>
    </van-panel>
    <!-- 新品首发 -->
    <van-panel title="新品首发">
      <div class="newGoodsList">
        <van-grid :border="false" :column-num="2">
          <van-grid-item v-for="(itemNewGoodsList,indexNewGoodsList) in newGoodsList" :key="indexNewGoodsList">
            <van-image width="100%" height="100%" lazy-load :src="itemNewGoodsList.list_pic_url" />
            <h4 class="title">{{itemNewGoodsList.name}}</h4>
            <p class="price">{{itemNewGoodsList.retail_price}}元起</p>
          </van-grid-item>
        </van-grid>
      </div>
    </van-panel>
    <!-- 新品首发 -->
    <van-panel title="新品首发">
      <div class="hotGoodsList">
        <van-card v-for="(itemHotGoodsList,indexHotGoodsList) in hotGoodsList" :key="indexHotGoodsList"
          :price="itemHotGoodsList.retail_price"
          :desc="itemHotGoodsList.goods_brief"
          :title="itemHotGoodsList.name"
          :thumb="itemHotGoodsList.list_pic_url"
        />
      </div>
    </van-panel>
    <!-- 标签栏 -->
    <div style="height:50px"></div>
    <tab-button></tab-button>
  </div>
</template>

<script>
import axios from 'axios'
import api from '../assets/config/api'
import Vue from 'vue';
import { Lazyload } from 'vant';
import tabButton from '../components/tabButton.vue';
Vue.use(Lazyload);

export default {
  name: 'home',
  data:function(){
    return {
      searchData:"",
      data:{}
    }
  },
  computed: {
    images:function(){
      if(this.data.banner){
        return this.data.banner
      }
      return []
    },
    channels:function(){
      if(this.data.channel){
        return this.data.channel
      }
      return []
    },
    brandList:function(){
      if(this.data.brandList){
        return this.data.brandList
      }
      return []
    },
    newGoodsList:function(){
      if(this.data.newGoodsList){
        return this.data.newGoodsList
      }
      return []
    },
    hotGoodsList:function(){
      if(this.data.hotGoodsList){
        return this.data.hotGoodsList
      }
      return []
    }
  },
  components: {
    tabButton
  },
  async mounted(){
    let res = await axios.get(api.IndexUrl)
    // console.log(res)
    this.data = res.data.data
  } 
}
</script>


<style lang="less">
  .home{
    .van-grid-item{
      overflow: hidden;
    }
    #swipeImage{
      width: 100%;
      height: 100%;
    }
    .brand{
      .van-grid-item__content{
        padding: 0;
      }
      .title{
        position: absolute;
        top: 20px;
        left: 10px;
      }
      .price{
        position: absolute;
        top: 40px;
        left: 10px;
        font-size: 14px;
        color:#999
      }
      .van-image{
        border: solid 1px white;
      }
    }

    .newGoodsList{
      .title{
        width:90%;
        overflow: hidden;
        white-space: nowrap;
        text-overflow: ellipsis;
      }
      .price{
        font-size: 14px;
        color:#999;
      }
    }

    .hotGoodsList{
      .van-card__content{
        justify-content: center;
        text-align: left;
      }
      .van-card__title{
        font-weight: 900;
        color:#333;
        font-size: 14px;
        padding: 5px 0;
      }
      .van-card__price{
        color: red;
      }
    }
  }
</style>