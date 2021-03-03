// pages/songDetail/songDetail.js
import request from '../../utils/request'
import PubSub from 'pubsub-js'
import moment from 'moment'

const appInstance = getApp();
Page({

  /**
   * 页面的初始数据
   */
  data: {
    isPlay: false,
    song:{},
    songId: "",
    musicLink:'',
    currentTime: '00:00',
    durationTime: '00:00',
    currentWidth: 0,
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) { 
    // console.log(options)
    let songId = options.songId;
    this.getMusicInfo(songId);
    this.setData({
      songId
    })
    //进入页面后直接播放
    this.handleMusicPlay();
    //判断当前页面音乐是否在播放
    if(appInstance.globalData.isMusicPlay && appInstance.globalData.songId === songId){
      this.setData({
        isPlay: true
      })
    }
    //创建音乐播放实例
    this.backgroundAudioManager = wx.getBackgroundAudioManager();
    //监听音乐播放暂停
    this.backgroundAudioManager.onPlay(() => {
      this.changePlayState(true)
      //修改全局音乐播放的状态
      appInstance.globalData.songId = songId;
    });
    this.backgroundAudioManager.onPause(() => {
      this.changePlayState(false)
    })
    this.backgroundAudioManager.onStop(() => {
      this.changePlayState(false)
    });
    //监听音乐播放结束
    this.backgroundAudioManager.onEnded(() => {
      // this.changePlayState(false)
      //自动播放下一首
      PubSub.publish('switchType', 'next')
      // 还原进度条，播放时间
      this.setData({
        currentWidth: 0,
        currentTime: '00:00',
      })
    });
    //监听音乐实时播放进度(s)
    this.backgroundAudioManager.onTimeUpdate(() => {
      let currentTime = moment(this.backgroundAudioManager.currentTime * 1000).format('mm:ss');
      let currentWidth = this.backgroundAudioManager.currentTime/this.backgroundAudioManager.duration * 450
      this.setData({
        currentTime,
        currentWidth
      })
    })
  },
  //修改音乐播放状态
  changePlayState(isPlay){
    this.setData({
      isPlay
    })
    //修改全局音乐播放的状态
    appInstance.globalData.isMusicPlay = isPlay;
  },

  //获取音乐详情
  async getMusicInfo(songId){
    let songData = await request('/song/detail', {ids: songId});
    // console.log(songData);
    //获取播放总时长，格式处理(mm)
    let durationTime = moment(songData.songs[0].dt).format('mm:ss');
    this.setData({
      song: songData.songs[0],
      durationTime,
    })
    //修改窗口标题
    wx.setNavigationBarTitle({
      title: this.data.song.name,
    })
  },

  //点击播放音乐
  handleMusicPlay(){
    let isPlay = !this.data.isPlay;
    let songId = this.data.songId;
    let musicLink = this.data.musicLink;
    this.musicControl(isPlay, songId, musicLink);
  },

  //控制音乐播放暂停
  async musicControl(isPlay, songId, musicLink){
    if(isPlay){
      //获取音乐播放链接
      if(!musicLink){
        let musicLinkData = await request('/song/url', {id:songId});
        musicLink = musicLinkData.data[0].url;
        this.setData({
          musicLink
        })
      }
      //设置音乐链接和title
      this.backgroundAudioManager.src = musicLink;
      this.backgroundAudioManager.title = this.data.song.name;
    }else{
      this.backgroundAudioManager.pause();
    }
  },
  //切换音乐
  handleSwitch(event){
    let type = event.currentTarget.id;  
    //关闭当前播放的音乐
    this.backgroundAudioManager.stop();
    //订阅来自recommendSong页面发布demusicId消息
    PubSub.subscribe('musicId',(msg,musicId) => {
      // console.log(musicId);
      //获取音乐详情信息
      this.getMusicInfo(musicId);
      //播放音乐
      this.musicControl('true',musicId);
      //取消订阅
      PubSub.unsubscribe('musicId');
    })
    //发布消息给recommendSong页面
    PubSub.publish('switchType', type)
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