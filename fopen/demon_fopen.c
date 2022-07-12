#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define FILEPATH ("./message.log")

/*****************************************************************************
*  函 数 名：main
*  功能描述：按时时间提取syslog
*  输入参数：int argc            
*            char const *argv[]  
*  输出参数：无
*  返 回 值：int
*  
*  修改历史：
*         1. 日    期：2022年7月12日
*            作    者：yinwenfeng
*            修改内容：新生成函数
*  
*****************************************************************************/
int main(int argc, char const *argv[])
{
	char *sBuff = NULL;
	unsigned int ulBuffSize = 0;
	char szLine[512] = {0};
	time_t pCurrentTime;
	char *sCurrentTime = NULL;
	
    FILE *pFile = fopen(FILEPATH, "r");
	if (!pFile)
	{
		printf("can not open %s: %s\n", FILEPATH, strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* 获取当前日期 */
	ctime(&pCurrentTime);
	printf("\r\n \033[1;35m[--ywf--]func: %s, line: %d\033[0m: sCurrentTime = %s\n", __FUNCTION__, __LINE__, sCurrentTime);

	
	/* 一次读取一行 */
	fseek(pFile, 0, SEEK_SET);
	sBuff = (char *)malloc(1);
	while (NULL != fgets(szLine, sizeof(szLine), pFile))
	{
		//提取时间
		

		
		ulBuffSize += strlen(szLine);
		sBuff = (char *)realloc(sBuff, ulBuffSize);
		if (NULL == sBuff )
		{
		    perror("realloc fail");
			return -1;
		}
		
		
		strcat(sBuff, szLine);
	}
	printf("%s", sBuff);
	free(sBuff);
	fclose(pFile);

	printf("\r\n \033[1;35m[--ywf--]func: %s, szLine: %d\033[0m: file size %fkb\n", __FUNCTION__, __LINE__, ulBuffSize/1024.0);
    return 0;
}

