<template>
  <div id="my">
    <div class="top">
      <div class="top1">
        <span style="margin-right: -100px">我的</span>
        <div class="border">
          <van-icon name="ellipsis" />
          <span style="color: grey"> | </span>
          <van-icon name="setting-o" />
        </div>
      </div>
      <div class="top2">
        <van-icon name="user-circle-o" size="60" />
        <span>点击登录</span>
        <div class="yuan">
          <van-icon name="arrow" style="padding: 2px 3px" />
        </div>
      </div>
    </div>

    <van-grid class="bottom" :border="true" :column-num="3">
      <van-grid-item>
        <van-icon name="orders-o" size="30" color="gray" @click="click"/>
        <p>我的订单</p>
      </van-grid-item>
      <van-grid-item>
        <van-icon name="cash-on-deliver" size="30" color="gray"/>
        <p>优惠卷</p>
      </van-grid-item>
      <van-grid-item>
        <van-icon name="gift-card-o" size="30" color="gray"/>
        <p>礼品卡</p>
      </van-grid-item>
      <van-grid-item>
        <van-icon name="home-o" size="30" color="gray"/>
        <p>我的收藏</p>
      </van-grid-item>
      <van-grid-item>
        <van-icon name="logistics" size="30" color="gray"/>
        <p>我的足迹</p>
      </van-grid-item>
      <van-grid-item>
        <van-icon name="gem-o" size="30" color="gray"/>
        <p>会员福利</p>
      </van-grid-item>
      <van-grid-item>
        <van-icon name="location-o" size="30" color="gray"/>
        <p>地址管理</p>
      </van-grid-item>
      <van-grid-item>
        <van-icon name="passed" size="30" color="gray"/>
        <p>账号安全</p>
      </van-grid-item>
      <van-grid-item>
        <van-icon name="chat-o" size="30" color="gray" />
        <p>联系客服</p>
      </van-grid-item>
      <van-grid-item>
        <van-icon name="question-o" size="30" color="gray" />
        <p>帮助中心</p>
      </van-grid-item>
      <van-grid-item>
        <van-icon name="records" size="30" color="gray" />
        <p>意见反馈</p>
      </van-grid-item>
    </van-grid>

    <tab-button></tab-button>
  </div>
</template>

<script>
import tabButton from "../components/tabButton.vue";
export default {
  data() {
    return {};
  },
  components: {
    tabButton,
  },
  methods:{
      click:function(){
          console.log("click");
      },
  }
};
</script>

<style lang="less">
#my {
  .top {
    background-color: rgba(15, 15, 15, 0.849);
    width: 100%;
    height: 180px;
    .top1 {
      padding-top: 25px;
      color: white;
      .border {
        border: 1px solid grey;
        border-radius: 45px;
        padding: 5px 15px;
        text-align: center;
        margin-right: 0px;
        float: right;
        margin-right: 20px;
      }
    }
    .top2 {
      margin-top: 50px;
      color: white;
      .van-icon {
        float: left;
        padding: 0 10px;
      }
      span {
        text-align: center;
        float: left;
        margin: 20px 5px;
      }
      .yuan {
        float: right;
        margin: 20px 5px;
        border: 1px solid grey;
        border-radius: 90px;
        height: 20px;
        width: 20px;
      }
    }
  }
  .bottom{
      font-size: 12px;
      color: gray;
  }
}
</style>