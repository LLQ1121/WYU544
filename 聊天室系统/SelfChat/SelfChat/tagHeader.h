typedef struct tagHeader
{
	char type; //��Ϣ����
	int len; //��Ϣ����
}Header,*pHeader;

#define LOGIN_IO 1 //������뿪
#define SEND_MESSAGE 3 //������Ϣ