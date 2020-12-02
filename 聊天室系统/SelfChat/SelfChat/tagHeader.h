typedef struct tagHeader
{
	char type; //消息类型
	int len; //消息长度
}Header,*pHeader;

#define LOGIN_IO 1 //进入和离开
#define SEND_MESSAGE 3 //发送消息