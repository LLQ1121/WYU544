<template>
  <div id="categoryList">
    <van-tabs v-model="active">
      <van-tab v-for="(item, index) in clist" :key="index" :title="item.name">
        <h3>{{ item.name }}</h3>
        <p>{{ item.front_name }}</p>
        <div v-if="item.plist">
          <van-grid :border="true" :column-num="2">
            <van-grid-item
              v-for="(item1, index1) in item.plist.data"
              :key="index1"
              :to="'/product/'+item1.id"
            >
              <van-image
                width="100"
                height="100"
                :src="item1.list_pic_url"
              />
              <h4 class="van-ellipsis">{{ item1.name }}</h4>
              <p class="price">${{item1.retail_price}}</p>
            </van-grid-item>
          </van-grid>
        </div>
      </van-tab>
    </van-tabs>

    <tab-button></tab-button>
  </div>
</template>

<script>
import tabButton from "../components/tabButton.vue";
import axios from "axios";
import api from "../assets/config/api.js";
export default {
  props: ["id"],
  data() {
    return {
      active: "",
      clist: [],
    };
  },
  components: {
    tabButton,
  },
  async created() {
    let res = await axios.get(api.GoodsCategory, { params: { id: this.id } });
    // console.log(res);
    this.clist = res.data.data.brotherCategory;
    let id = this.clist[0].id;
    this.clist.forEach(async (item, index) => {
      item.plist = await this.getlist(item.id, 1);
      // console.log(item.plist.data)
      this.$forceUpdate();
    });
  },
  // watch: {
  //   active: async function (index) {
  //     let id = this.clist[index].id;
  //     let page = 1;
  //     let size = 20;
  //   },
  methods: {
    async getlist(id, page) {
      let res = await axios.get(api.GoodsList, {
        params: { categoryId: id, page },
      });
      return res.data.data;
    },
  },
};
</script>

<style lang="less">
  #categoryList{
    .van-ellipsis{
      width: 100%;
      font-size: 14px;
      font-weight: 500;
      padding: 0 10px;
    }
    .van-grid-item{
      overflow: hidden;
      box-sizing: border-box;
    }
    .price{
      color: red;
    }
  }
</style>