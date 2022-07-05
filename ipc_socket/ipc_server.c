#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>


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

2.bind
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

return: 失败返回-1
param @addr:
	一般使用sockaddr_in、sockaddr_un结构体
	sockaddr_in用于不同主机间socket编程
	sockaddr_un用于同一主机内部socket编程，例如：进程间通信
param @addrlen:


3.int listen(int sockfd, int backlog);
param @backlog:
	最大监听数量

4.有客户端接入accept，
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
第二个参数为客户端地址，第三个参数为客户端地址的长度。
如果不关心客户端的地址第二第三个参数可以传NULL	

5.select 
int select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout);

*/

#define SOCK_PATH ("/tmp/acCtrl.sock")


/*****************************************************************************
*  函 数 名：main
*  功能描述： 
*  输入参数：int argc            
*            const char *argv[]  
*  输出参数：无
*  返 回 值：int
*  
*  修改历史：
*         1. 日    期：2022年5月5日
*            作    者：yinwenfeng
*            修改内容：新生成函数

*****************************************************************************/
int main(int argc, const char *argv[])
{
	int i = 0;
	int j = 0;
	int maxfd = 0;
	int ret = 0;
	int fdServer = 0;
	int newfd = 0;
	int fdClnt[5] = {0};
	int clntCnt = 0;
	fd_set readfd;
	struct sockaddr_un addrMsg;
	memset(&addrMsg, 0, sizeof(addrMsg));

	//1.创建套接字
    fdServer = socket(AF_UNIX, SOCK_STREAM, 0);
	if (-1 == fdServer)
	{
		perror("socket");
		return -1;
	}

	//2.bind 为套接字添加信息（IP，port)
	unlink(SOCK_PATH);//清除.sock文件
	addrMsg.sun_family = AF_UNIX;
	strcpy(addrMsg.sun_path , SOCK_PATH);
	ret = bind(fdServer, (struct sockaddr *)&addrMsg, sizeof(addrMsg));
	if ( -1 == ret )
	{
		perror("bind");
		close(fdServer);
		unlink(SOCK_PATH);
		return -1;
	}
	
	//3.监听网络连接listen
	ret = listen(fdServer, 5);
	if (-1 == ret)
	{
		perror("listen");
		close(fdServer);
		unlink(SOCK_PATH);
		return -1;
	}

	maxfd = fdServer;
	while(1)
	{
		
		char readBuff[256] = {0};
		struct timeval timeout;
		memset(&timeout, 0, sizeof(timeout));
		
		FD_ZERO(&readfd);	//清空监视集合
		FD_SET(fdServer, &readfd);	//添服务端fd到监视
        for (i = 0; i < 5; i++)		//添加客户端fd
        {
            printf("fdclnt[%d] = %d\n", i, fdClnt[i]);
            if ( 0 != fdClnt[i])
            {
                FD_SET(fdClnt[i], &readfd);
            }
        }
		
		timeout.tv_sec = 2;

		printf("select...current[%d]\n", clntCnt);
		ret = select(maxfd + 1, &readfd, NULL, NULL, &timeout);
		if(-1 == ret)//出错
		{
		    perror("select");
			break;
		}
		else if (0 == ret)//超时
		{
//		    printf("select time out\n");
		}
		else
		{
			//区分描述符，是接受连接请求还是读写操作
			if (FD_ISSET(fdServer, &readfd)) //服务端，接受链接请求
			{
				int newClnt = accept(fdServer, NULL, NULL); 
				if (-1 == newClnt)
				{
				    perror("accept");
					continue;
				}

				if (clntCnt < 5)
				{
					fdClnt[clntCnt] = newClnt;
					if (newClnt > maxfd)
					{
						maxfd = newClnt;
					}
					clntCnt++;
					printf("new clinet conneted\n");
				    
				}
				else
				{
					close(newClnt);
					newClnt = 0;
				    printf("clinet full\n");
				}
				
			}

			for (i = 0 ; i < 5; i++) //客户端fd，读写
			{
				if (FD_ISSET(fdClnt[i], &readfd))
				{
					//读取内容
					int lenth = read(fdClnt[i], readBuff, sizeof(readBuff));
					if (-1 == lenth)
					{
						printf("\n\033[47;35m[--ywf-->%s, %d]:\033[0m %s\n", __FUNCTION__, __LINE__, strerror(errno));
						close(fdClnt[i]);
						fdClnt[i] = 0;
						clntCnt--;
						
						//删除一个后，数组后面的需要往前移动
						for (j = i; j < 5; j++)
						{
							if (4 == j) //处理越界
							{
							    fdClnt[j] = 0;
							}
							else
							{
							    fdClnt[j] = fdClnt[j+1];
							}	
						}
						
					}
					else if (0 == lenth)
					{
					    printf("client disconneted\n");
						close(fdClnt[i]);
						fdClnt[i] = 0;
						clntCnt--;

						//删除一个后，数组后面的需要往前移动
						for (j = i; j < 5; j++)
						{
							if (4 == j) //处理越界
							{
							    fdClnt[j] = 0;
							}
							else
							{
							    fdClnt[j] = fdClnt[j+1];
							}	
						}
					}
					else
					{
						printf("read from socket %d : %s\n", fdClnt[i], readBuff);
						
						//写
						lenth = write(fdClnt[i], readBuff, strlen(readBuff));
						if (-1 == lenth)
						{
							perror("write");
						} 	    
					}	
				}
			    
			}
				  
			
			
		}	
	}

	for ( i = 0 ; i < 5; i++ )
	{
		if (0 != fdClnt[i])
		{
		    close(fdClnt[i]);
		}
	}
	close(fdServer);
	unlink(SOCK_PATH);
	
	return 0;   
}
