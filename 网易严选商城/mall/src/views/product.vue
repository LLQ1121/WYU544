<template>
  <div id="product">
    <van-nav-bar
      title="商品"
      left-text="返回"
      left-arrow
      @click-left="onClickLeft"
    />

    <van-swipe :autoplay="3000">
      <van-swipe-item v-for="(image, index) in images" :key="index">
        <img class="swipeImg" v-lazy="image.img_url" />
      </van-swipe-item>
    </van-swipe>

    <div class="info">
      <span>30天无忧退货</span>
      <span>48小时极速退款</span>
      <span>满88免邮费</span>
    </div>

    <div class="info2">
      <h3 class="name">{{ info.name }}</h3>
      <p class="brief">{{ info.goods_brief }}</p>
      <p class="price">￥{{ info.retail_price }}</p>
    </div>

    <van-cell title="请选择规格数量" is-link />

    <div class="proParams">
      <h3>商品参数</h3>
      <div class="proItem" v-for="(item, index) in attribute" :key="index">
        <span class="name">{{ item.name }}</span>
        <span class="value">{{ item.value }}</span>
      </div>
    </div>

    <div class="proDetail" v-html="info.goods_desc"></div>

    <van-goods-action>
      <van-goods-action-icon to="/buycart" :info="$store.state.cartTotal.goodsCount==0?'':$store.state.cartTotal.goodsCount" icon="cart-o" text="购物车" />
      <van-goods-action-icon icon="star" text="已收藏" color="#ff5000" />
      <van-goods-action-button @click="chooseSku" type="warning" text="加入购物车"/>
      <van-goods-action-button type="danger" text="立即购买" />
    </van-goods-action>
    <!-- 商品规格 -->
    <van-sku
      v-model="showSku"
      :sku="sku"
      :goods="goods"
      @buy-clicked="onBuyClicked"
      @add-cart="onAddCartClicked"
    />
  </div>
</template>

<script>
import axios from "axios";
import api from "../assets/config/api.js";
export default {
  props: ["id"],
  data() {
    return {
      data: {},
      info: {},
      attribute: {},
      showSku: false,
      sku: {
        // 所有sku规格类目与其值的从属关系，比如商品有颜色和尺码两大类规格，颜色下面又有红色和蓝色两个规格值。
        // 可以理解为一个商品可以有多个规格类目，一个规格类目下可以有多个规格值。
        tree: [
          {
            k: "颜色", // skuKeyName：规格类目名称
            k_s: "s1", // skuKeyStr：sku 组合列表（下方 list）中当前类目对应的 key 值，value 值会是从属于当前类目的一个规格值 id
            v: [
              {
                id: "1", // skuValueId：规格值 id
                name: "", // skuValueName：规格值名称
              },
              {
                id: "2",
                name: "",
              },
            ],
            largeImageMode: true, //  是否展示大图模式
          },
        ],
        list: [
          {
            id: 2259, // skuId
            's-1': "1", // 规格类目 k_s 为 s1 的对应规格值 id
            's-2': "3", // 规格类目 k_s 为 s2 的对应规格值 id
            price: 100, // 价格（单位分）
            stock_num: 110, // 当前 sku 组合对应的库存
          },
          {
            id: 2259, // skuId
            's-1': "2", // 规格类目 k_s 为 s1 的对应规格值 id
            's-2': "4", // 规格类目 k_s 为 s2 的对应规格值 id
            price: 100, // 价格（单位分）
            stock_num: 120, // 当前 sku 组合对应的库存
          },
        ],
        // 所有 sku 的组合列表，比如红色、M 码为一个 sku 组合，红色、S 码为另一个组合
        price: "1.00", // 默认价格（单位元）
        stock_num: 260, // 商品总库存
      },
      goods: {
        // 默认商品 sku 缩略图
        picture: "",
      },
    };
  },
  methods: {
    onClickLeft: function () {
      this.$router.go(-1);
    },
    onBuyClicked: function () {},
    async onAddCartClicked(skuData) {
      this.showSku = false;
      // console.log(skuDate)
      let chooseContent = skuData.selectedSkuComb['s-1']+'_'+skuData.selectedSkuComb['s-2']
      // console.log(chooseContent)
      let resultPro = this.data.productList.filter((item,index) =>{
        if(item.goods_specification_ids == chooseContent){
          return true
        }else{
          return false
        }
      })
      // console.log(resultPro)
      let cartRes = await axios.post(api.CartAdd,{ goodsId:resultPro[0].goods_id , number: skuData.selectedNum, productId: resultPro[0].id })
      // console.log(cartRes.data)
      this.$store.commit('setCartList',cartRes.data.data.cartList),
      this.$store.commit('setCartTotal',cartRes.data.data.cartTotal)
    },
    chooseSku: function () {
      this.showSku = true;
    },
  },
  computed: {
    images: function () {
      if (this.data.gallery == undefined) {
        return [];
      } else {
        return this.data.gallery;
      }
    },
  },
  async created() {
    this.$store.dispatch('AjaxCart');
    let res = await axios.get(api.GoodsDetail, { params: { id: this.id } });
    this.data = res.data.data;
    // console.log(this.data);
    this.info = this.data.info;
    this.attribute = this.data.attribute;
    this.goods.picture = this.info.primary_pic_url;
    this.sku.price = this.info.retail_price;
    this.sku.stock_num = this.info.goods_number;
    let tree = [];

    this.data.specificationList.forEach((item, index) => {
      let arr = [];
      item.valueList.forEach((product, i) => {
        arr.push({
          id: product.id,
          name: product.value,
        });
      });
      tree.push({
          k: item.name,
          v: arr,
          k_s: "s-" + item.specification_id,
        });
    });
    this.sku.tree = tree;
  },
};
</script>

<style lang="less">
#product {
  .swipeImg {
    width: 100%;
  }
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
  .info2 {
    .name {
      font-weight: 500;
      padding: 10px 0 5px;
    }
    .brief {
      font-size: 12px;
      color: #999;
      padding: 3px;
    }
    .price {
      font-size: 16px;
      color: red;
      padding: 5px;
    }
  }
  .van-cell__title {
    text-align: left;
  }
  .proParams {
    padding-bottom: 20px;
    h3 {
      padding: 10px 0;
    }
    .proItem {
      width: 90%;
      margin: 0 auto;
      display: flex;
      justify-content: space-between;
      height: 24px;
      color: #999;
      font-size: 12px;
      background: #efefef;
      line-height: 24px;
      text-align: left;
      .name {
        width: 45px;
        padding: 0 10px;
        border-right: 1px solid #ccc;
      }
      .value {
        width: 260px;
        overflow: hidden;
        text-overflow: ellipsis;
        white-space: nowrap;
      }
    }
  }
  .proDetail {
    width: 100%;
    img {
      width: 100%;
    }
    p {
      margin: 0;
      padding: 0;
      display: flex;
    }
  }
}
</style>