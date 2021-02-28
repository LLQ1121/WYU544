<template>
    <van-tabbar v-model="active">
      <van-tabbar-item icon="wap-home-o" to="/">首页</van-tabbar-item>
      <van-tabbar-item icon="goods-collect-o" to="/topic">专题</van-tabbar-item>
      <van-tabbar-item icon="apps-o" to="/category">分类</van-tabbar-item>
      <van-tabbar-item icon="shopping-cart-o" to="/buycart">购物车</van-tabbar-item>
      <van-tabbar-item icon="manager-o" to="/my">我的</van-tabbar-item>
    </van-tabbar>
</template>

<script>
export default {
    data(){
        return{
            active: 0
        }
    },
    mounted(){
        switch(this.$route.path){
            case "/":
                this.active = 0;
                break;
            case "/topic":
                this.active = 1;
                break;
            case "/category":
                this.active = 2;
                break;
            case "/buycart":
                this.active = 3;
                break;
            case "/my":
                this.active = 4;
                break;
            default:
                this.active = 0;
        }
    }
}
</script>