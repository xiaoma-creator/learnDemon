#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <errno.h>

/*  
#include <sys/socket.h>

socket服务端开发步骤：
创建套接字sock->为套接字添加信息（IP地址和端口号）bind->监听网络连接listeb->有客户端接入accept，
接受一个连接->数据交互->关闭套接字，断开连接 read write close

1.创建套接字
int sockfd = socket(int socket_family, int socket_type, int protocol);

return:失败返回-1
param @socket_family:
	指定地址族(AF:address family)
	常用：
		1.AF_INET		ipv4因特网
		2.AF_INET6		IPV6因特网
		3.AF_UNIX		Unix域、linux进程通信
	也可以使用PF开头的，作用跟AF一样
	
param @socket_type:
	指定socket类型：
		1.SOCK_STREAM		流式套接字，使用tcp协议，保证数据传输可靠
		2.SOCK_DGRAM		数据报套接字，使用udp协议
		3.SOCK_RAW			允许使用底层协议，如IP或ICMP，一般用于协议开发

param @protocol:
	指定协议：
		1.一般填0：			使用socket_type对应的默认协议
		2.IPPROTO_TCP
		3.IPPROTO_UDP
		4.IPPROTO_SCTP


4.connect，
#include <sys/types.h>       
#include <sys/socket.h>

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

*/

#define SOCK_PATH ("/tmp/acCtrl.sock")

int main(int argc, const char *argv[])
{
	int fd_clnt = 0;
	int ret = 0;
	struct sockaddr_un addrMsg;
	memset(&addrMsg, 0, sizeof(addrMsg));

	//1.创建套接字
    fd_clnt = socket(AF_UNIX, SOCK_STREAM, 0);
	if (-1 == fd_clnt)
	{
		printf("\n\033[47;35m[--ywf-->%s, %d]:\033[0m fd_clnt socket error\n", __FUNCTION__, __LINE__);
		perror("socket:");
		printf("socket:%s", strerror(errno));
		return -1;
	}

	//2.bind 为套接字添加信息（IP，port)
	addrMsg.sun_family = AF_UNIX;
	strcpy(addrMsg.sun_path , SOCK_PATH);

	//链接服务器
	ret = connect(fd_clnt, (struct sockaddr *)&addrMsg, sizeof(addrMsg));
	if (-1 == ret)
	{
	    perror("connect");
		return -1;
	}
	
	while(1)
	{
		char str[256] = {0};
		int lenth = 0;
		
		scanf("%s", str);
        if(!strcmp(str, "quit"))
        {
            break;
        }
        
		lenth = write(fd_clnt, str, strlen(str));
		if (-1 == lenth)
		{
		    perror("write");
		}

		memset(str, 0, sizeof(str));
		lenth = read(fd_clnt, str, sizeof(str));
		if (-1 == lenth)
		{
		    perror("read");
		}

		printf("read = %s\n", str);
	}

    close(fd_clnt);
    
	return 0;   
}

