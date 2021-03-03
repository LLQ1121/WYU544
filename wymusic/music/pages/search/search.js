// pages/search/search.js
import request from '../../utils/request'
Page({

  /**
   * 页面的初始数据
   */
  data: {
    placeholderContent: '',
    hotList: [],
    searchContent: '', //输入表单内容
    searchList: [], //模糊匹配的数据
    isSend: false,
    historyList: [],
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    this.getInitData();
    this.getSearchHistory();  
  },

  async getInitData(){
    let placeholderData = await request('/search/default');
    // console.log(placeholderData);
    let hotListData = await request('/search/hot/detail');
    // console.log(hotListData);
    this.setData({
      placeholderContent: placeholderData.data.showKeyword,
      hotList: hotListData.data
    })
  },  
  //获取本地历史记录
  getSearchHistory(){
    let historyList = wx.getStorageSync('searchHistory');
    if(historyList){
      this.setData({
        historyList
      })
    }
  },

  //表单内容改变时
  handleInput(event){
    this.setData({
      searchContent: event.detail.value.trim()
    })
    //函数节流
    if(this.data.isSend){
      return;
    }
    this.setData({
      isSend: true
    })
    this.getSearchList();
    setTimeout(() => {
      this.setData({
        isSend: false
      })
    }, 300);
  },
  //获取的搜索数据
  async getSearchList(){
    //搜索框为空时不进行搜索
    if(!this.data.searchContent){
      this.setData({
        searchList: [],
      })
      return;
    }
    //模糊匹配
    let {searchContent, historyList} = this.data;
    let searchListData = await request('/search', {keywords: this.data.searchContent, limit: 10});
    this.setData({
      searchList: searchListData.result.songs
    })
    //将搜索的关键字添加到搜索历史记录中
    if(historyList.indexOf(searchContent) !== -1){
      historyList.splice(historyList.indexOf(searchContent),1)
    }
    historyList.unshift(searchContent);
    // this.setData({
    //   historyList
    // })
    wx.setStorageSync('searchHistory', historyList)
  },
  //清空搜索内容
  clearSearchContent(){
    this.setData({
      searchContent: '',
      searchList: [],
    })
  },
  //删除搜索历史记录
  deleteSearchHistory(){
    wx.showModal({
      content: '确认删除吗?',
      success: (res) => {
        if(res.confirm){
          this.setData({
            historyList: []
          })
          wx.removeStorageSync('searchHistory');
        }
      }
    })
  },
  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  }
})