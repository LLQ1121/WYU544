// 封装 请求
import config from './config'
export default(url,data={},method="GET") => {
  return new Promise((resolve,reject) => {
    wx.request({
      url: config.host + url,
      data,
      method,
      header:{
        cookie: wx.getStorageSync('cookies')?wx.getStorageSync('cookies').find(item=>item.indexOf('MUSIC_U') !== -1):''
      },
      success:(res)=>{
        if(data.isLogin){
          wx.setStorage({
            key: 'cookies',
            data: res.cookies
          })
        }
        // console.log('成功',res);
        resolve(res.data); //修改promise为成功resolve状态
        // console.log(res.data);
      },
      fail:(err)=>{
        // console.log('失败',err);
        reject(err); //修改promise为失败reject状态
      }
    })
  })
}