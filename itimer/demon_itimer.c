#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
/* 
	主要运作过程：itimer将itimerval里面的it_value递减，当it_value
	减为0时触发SIGALRM信号，然后将itimerval里面的it_interval的值赋给it_value
	循环执行下去,任何时刻将it_value设置为0，定时器都会停止
*/

/*****************************************************************************
*  函 数 名：itimer_init
*  功能描述：初始化定时器
*  输入参数：int i_timeMs 定时长度ms  
			 int i_flagOnce 触发标志，1：只触发一次 0：循环触发
*  输出参数：无
*  返 回 值：void
*  
*  修改历史：
*         1. 日    期：2022年7月5日
*            作    者：yinwenfeng
*            修改内容：新生成函数
*  
*****************************************************************************/
void itimer_init(int i_timeMs, int i_flagOnce)
{
    struct itimerval st_newValue;
	
	memset(&st_newValue, 0, sizeof(struct itimerval));
	if (!i_flagOnce)
	{
		st_newValue.it_interval.tv_sec = i_timeMs/1000;
		st_newValue.it_interval.tv_usec = i_timeMs%1000;	    
	}
	st_newValue.it_value.tv_sec = i_timeMs/1000;
	st_newValue.it_value.tv_usec = i_timeMs%1000;
	
    setitimer(ITIMER_PROF, &st_newValue, NULL);
	
}

/*****************************************************************************
*  函 数 名：itimer_sighandler
*  功能描述：信号处理
*  输入参数：int signo  
*  输出参数：无
*  返 回 值：void
*  
*  修改历史：
*         1. 日    期：2022年7月5日
*            作    者：yinwenfeng
*            修改内容：新生成函数
*  
*****************************************************************************/
void itimer_sighandler(int signo)
{
	switch ( signo )
	{
	    case SIGPROF:
    		printf("\r\n \033[1;35m[--ywf--]func: %s, line: %d\033[0m: SIGALRM\n", __FUNCTION__, __LINE__);
	        break;
	    default:
			printf("\r\n \033[1;35m[--ywf--]func: %s, line: %d\033[0m: default\n", __FUNCTION__, __LINE__);
	        break;
	}

}

void itimer_init_sigaction()
{
    struct sigaction act;
	act.sa_handler = itimer_sighandler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGPROF, &act, NULL);

}
/*****************************************************************************
*  函 数 名：main
*  功能描述：主函数
*  输入参数：int argc            
*            char const *argv[]  
*  输出参数：无
*  返 回 值：int
*****************************************************************************/
int main(int argc, char const *argv[])
{	
	itimer_init(1000, 0);
	itimer_init_sigaction();
	while(1){
//		usleep(100);
	}
	
    return 0;
}

