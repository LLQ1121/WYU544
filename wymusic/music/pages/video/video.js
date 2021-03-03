// pages/video/video.js
import request from '../../utils/request'
Page({

  /**
   * 页面的初始数据
   */
  data: {
    videoGroupList: [],
    navId: '',
    videoList: [],
    videoId: '',
    videoUpdateTime: [],
    isTriggered: false,
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    this.getVideoGroupListData();
  },
  //获取导航数据
  async getVideoGroupListData(){
    let videoGroupListData = await request('/video/group/list');
    this.setData({
      videoGroupList: videoGroupListData.data.slice(0,14),
      navId: videoGroupListData.data[0].id
    })
    this.getVideoList(this.data.navId)
  },
  //获取视频列表数据
  async getVideoList(navId){
    if(!navId){
      return;
    }
    let videoListData = await request('/video/group',{id:navId})
    // console.log(videoListData);
    wx.hideLoading(); //关闭消息提示框
    let index = 0;
    let videoList = videoListData.datas.map(item => {
      item.id = index++;
      return item;
    })
    this.setData({
      videoList,
      isTriggered: false //关闭下拉刷新
    })
    // console.log(videoList);
  },
  //点击切换导航
  changeNav(event){
    let navId = event.currentTarget.id;
    // console.log(event);
    // console.log(parseInt(navId))
    this.setData({
      navId: parseInt(navId),
      videoList:[]
    })
    wx.showLoading({
      title: '正在加载',
    })
    this.getVideoList(this.data.navId)
  },
  //点击/继续播放
  handlePlay(event){
    let vid = event.currentTarget.id;
    // this.vid !== vid && this.videoContext && this.videoContext.stop();
    // this.vid = vid;
    this.setData({
      videoId: vid
    })
    this.videoContext = wx.createVideoContext(vid);
    let {videoUpdateTime} = this.data;
    let videoItem = videoUpdateTime.find(item => item.vid === vid);
    if(videoItem){
      this.videoContext.seek(videoItem.currentTime);
    }
    this.videoContext.play(); 
  },
  //监听视频播放进度
  handleTimeUpdate(event){
    let videoTimeObj = {vid: event.currentTarget.id, currentTime: event.detail.currentTime};
    let {videoUpdateTime} = this.data;
    let videoItem = videoUpdateTime.find(item => item.vid === videoTimeObj.vid);
    if(videoItem){
      videoItem.currentTime = event.detail.currentTime;//如果之前播放过则更新时长
    }else{
      videoUpdateTime.push(videoTimeObj);//没有则将当前播放对象存进数组
    }
    this.setData({
      videoUpdateTime
    })
  },
  //视频播放结束
  handleEnded(event){
    let {videoUpdateTime} = this.data;
    videoUpdateTime.splice(videoUpdateTime.findIndex(item => item.vid === event.currentTarget.id),1);
    this.setData({
      videoUpdateTime
    })
  },
  //下拉刷新
  handleRefresher(){
    this.getVideoList(this.data.navId);
  },

  toSearch(){
    wx.navigateTo({
      url: '/pages/search/search'
    })
  },

  //上拉触底 显示更多内容 网易云暂无api接口
  handleTolower(){
    //
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
    return{
      title: '转发给你的好友'
    }
  }
})