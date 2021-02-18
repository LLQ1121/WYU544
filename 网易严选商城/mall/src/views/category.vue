<template>
  <div id="category">
    <van-search
      input-align="center"
      placeholder="请输入搜索关键词"
      :v-model="searchData"
    />

    <van-tree-select
      height="100vh - 104ph"
      :items="items"
      :main-active-index.sync="activeIndex"
      @click-nav="changeRight"
    >
      <template #content>
        <div class="bannerImg">
            <img width="100%" :src="bannerImg" alt="">
        </div>
        <van-grid :column-num="3">
          <van-grid-item
            v-for="(item, index) in subCategoryList"
            :key="index"
            :icon="item.wap_banner_url"
            :text="item.name"
            :to="'/categoryList/' + item.id"
          />
        </van-grid>
      </template>
    </van-tree-select>

    <tab-button></tab-button>
  </div>
</template>

<script>
import tabButton from "../components/tabButton.vue";
import axios from "axios";
import api from "../assets/config/api.js";
export default {
  data() {
    return {
      searchData: "",
      activeIndex: 0,
      subCategoryList: [],
      //   items: [{ text: '分组 1' }, { text: '分组 2' }],
      data: {},
      bannerImg: ""
    };
  },
  async created() {
    let res = await axios.get(api.CatalogList);
    this.data = res.data.data;
    // console.log(res);
    this.subCategoryList = this.data.currentCategory.subCategoryList;
    this.bannerImg = this.data.currentCategory.img_url
  },
  computed: {
    items: function () {
      if (this.data.categoryList == undefined) {
        return [];
      } else {
        let arr = [];
        this.data.categoryList.forEach((item, index) => {
          item.text = item.name;
          arr.push(item);
        });
        return arr;
      }
    },
  },
  methods: {
    changeRight: function (index) {
      this.activeIndex = index;
    },
  },
  watch: {
    activeIndex: async function () {
      if (this.items.length !== 0) {
        let id = this.items[this.activeIndex].id;
        let res = await axios.get(api.CatalogCurrent, { params: { id } });
        this.subCategoryList = res.data.data.currentCategory.subCategoryList;
        this.bannerImg = this.items[this.activeIndex].img_url
      } else {
        this.subCategoryList = [];
      }
    },
  },
  components: {
    tabButton,
  },
};
</script>

<style lang="less">
    #category{
        .bannerImg{
            width: 100%;
            box-sizing: border-box;
            padding: 0px 5px 0px 0px;
        }
    }
</style>