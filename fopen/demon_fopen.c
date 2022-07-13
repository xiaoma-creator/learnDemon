#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define FILEPATH ("./keymessage.log")

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
	char szLine[512] = {0};
	char *sBuff = NULL;
	char *sMoreMemory = NULL;
	char *sCurrentTime = NULL;
	unsigned long ulBuffSize = 0;
	time_t SCurrentTime;
	struct tm *pSLocalTime = NULL;
	
	
	/* 获取当前日期 */
	SCurrentTime = time(NULL);
	pSLocalTime = localtime(&SCurrentTime);
    

	FILE *pFile = fopen(FILEPATH, "r");
	if (!pFile)
	{
		printf("can not open %s: %s\n", FILEPATH, strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* 一次读取一行 */
	fseek(pFile, 0, SEEK_SET);
	while (NULL != fgets(szLine, sizeof(szLine), pFile))
	{
		ulBuffSize += strlen(szLine);
		
		sMoreMemory = (char *)realloc(sBuff, ulBuffSize + 1);
		if (NULL == sMoreMemory )
		{
			if (NULL != sBuff)
			{
			    free(sBuff);
			}
		    perror("realloc fail");
			return -1;
		}

		sBuff = sMoreMemory;
		memcpy(sBuff+ulBuffSize-strlen(szLine), szLine, strlen(szLine));
        sBuff[ulBuffSize] = '\0';
	}
	printf("%s", sBuff);

    if (NULL != sBuff)
    {
	    free(sBuff);
    }

    if (NULL != pFile)
    {
	    fclose(pFile);
    }

	printf("\r\n \033[1;35m[--ywf--]func: %s, szLine: %d\033[0m: file size %ld byte\n", __FUNCTION__, __LINE__, ulBuffSize);

    return 0;
}

