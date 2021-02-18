<template>
  <div id="topic">
    <div class="list" v-for="(item, index) in this.data.data" :key="index">
      <van-card
        :num="item.id"
        :price="item.price_info"
        :desc="item.subtitle"
        :title="item.title"
        :thumb="item.scene_pic_url"
      />
    </div>
    <div style="height: 50px"></div>
    <tab-button></tab-button>
  </div>
</template>

<script>
import axios from "axios";
import api from "../assets/config/api.js";
import tabButton from "../components/tabButton.vue";
export default {
  data() {
    return {
      data: {},
    };
  },
  components: {
    tabButton,
  },
  created() {},
  async mounted() {
    let res = await axios.get(api.TopicList);
    this.data = res.data.data;
    console.log(this.data);
  },
};
</script>

<style lang="less">
#topic {
  .list {
      .van-card__content{
          border: #efefef solid 1px;
        //   background: #efefef;
      }

       .van-image{
          background: #efefef;
          .van-image__img {
              width: 100%;
              width: 100%;
          }
      }
      .van-card__title{
        width: 100%;
        font-size: 14px;
        justify-content: space-between;
        padding-top: 20px;
      }
      .van-card__desc{
        width: 100%;
        font-size: 12px;
        font-weight: 500;     
        text-align: center;
      }
      .van-card__bottom{
          padding-bottom: 5px;
      }
  }
}
</style>