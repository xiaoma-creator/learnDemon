#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define FILEPATH ("./keymessage.log")
#define EMPTYFILE ("./empty.txt")

int read_file_by_line(const char *sFileName, char **pcDst);
int read_line_from_tail(const char *psFilename, int iTargetLine, char **ppBuff);

/*****************************************************************************
*  函 数 名：main
*  功能描述：将文件读取到内存中
*  输入参数：int argc            
*            char const *argv[]  
*  输出参数：无
*  返 回 值：int

*****************************************************************************/
int main(int argc, char const *argv[])
{
    char *sContent = NULL;

    int iResult = read_file_by_line(EMPTYFILE, &sContent);
    if(0 == iResult)
    {
        printf("read file failed\n");
    }
    printf("%s\n", sContent);

    if (sContent != NULL)
    {
        free(sContent);
        sContent = NULL;
    }

    iResult = read_line_from_tail(FILEPATH, 10, &sContent);
    if (iResult == 0)
    {
        
    }
    printf("%s", sContent);

    return 0;
}

/*****************************************************************************
*  函 数 名：read_line
*  功能描述：从文件末尾读取 iTargetLine 行
*  输入参数：pSFile 文件指针
            iTargetLine 需要读取的行数          
*  输出参数：buff 存储位置
*  返 回 值：成功返回读取到内容首地址
            失败返回NULL

*****************************************************************************/
int read_line_from_tail(const char *psFilename, int iTargetLine, char **ppDest)
{
    char cCh = 0;
    char szLine[512] = {0};
    char *sBuff = NULL;
    char *psMoreMemory = NULL;
    char cFlagFirstLine = 0;
    unsigned long ulBuffSize = 0;

    long iIndex = 0;
    int iLineCnt = 0;

    if (psFilename == NULL)
    {
        return 0;
    }
    if (iTargetLine <= 0)
    {
        return 0;
    }

    FILE *pSFile = fopen(psFilename, "r");
	if (NULL == pSFile)
	{
		printf("can not open %s: %s\n", psFilename, strerror(errno));
		exit(EXIT_FAILURE);
	} 

    /* 判断文件为空 */
    if (fgetc(pSFile) == EOF)
    {
        fclose(pSFile);
        sBuff = (char *)malloc(1);
        sBuff[0] = '\0';
        *ppDest = sBuff;
        return 1;
    }

    iIndex = -1;
    while(iLineCnt < iTargetLine)
    {
        fseek(pSFile, iIndex, SEEK_END);
        cCh = fgetc(pSFile);
        putchar(cCh);
        if (cCh == '\n')
        {
            if (NULL == fgets(szLine, sizeof(szLine), pSFile))
            {
                break;
            }

            ulBuffSize += strlen(szLine);
            psMoreMemory = (char *)realloc(sBuff, ulBuffSize+1);
            if (psMoreMemory == NULL)
            {
                if (NULL != sBuff)
                {
                    free(sBuff);
                }
                perror("realloc fail");
                return 0;
            }

            sBuff = psMoreMemory;
            memcpy(sBuff+ulBuffSize-strlen(szLine), szLine, strlen(szLine));
            sBuff[ulBuffSize] = '\0';
            iLineCnt++;
            iIndex -= 2;
            continue;    
        }
        iIndex--;
    }

    if (pSFile != NULL)
    {
        fclose(pSFile);
        pSFile = NULL;
    }

    return 1;
}

/*****************************************************************************
*  函 数 名：
*  功能描述：
*  输入参数：
*  输出参数：无
*  返 回 值：
            0:出错
            1:成功

*****************************************************************************/
int read_file_by_line(const char *sFileName, char **pcDst)
{
	char szLine[512] = {0};
	char *sBuff = NULL;
	char *sMoreMemory = NULL;
	unsigned long ulBuffSize = 0;

    if (sFileName == NULL)
    {
        return 0;
    }

	FILE *pFile = fopen(sFileName, "r");
	if (NULL == pFile)
	{
		printf("can not open %s: %s\n", sFileName, strerror(errno));
		return 0;
	}

    /* 判断文件是否为空 */
    if (fgetc(pFile) == EOF)
    {
        fclose(pFile);
        sBuff = (char *)malloc(1);
        sBuff[0] = '\0';
        *pcDst = sBuff;
        return 1;
    }

	/* 一次读取一行 */
	fseek(pFile, 0, SEEK_SET);
	while (NULL != fgets(szLine, sizeof(szLine), pFile))
	{
		ulBuffSize += strlen(szLine);
		
		sMoreMemory = (char *)realloc(sBuff, ulBuffSize+1);
		if (NULL == sMoreMemory )
		{
			if (NULL != sBuff)
			{
			    free(sBuff);
			}
		    perror("realloc fail");
			return 0;
		}

		sBuff = sMoreMemory;
		memcpy(sBuff+ulBuffSize-strlen(szLine), szLine, strlen(szLine));
        sBuff[ulBuffSize] = '\0';
	}

    if (NULL != pFile)
    {
	    fclose(pFile);
        pFile = NULL;
    } 

    *pcDst = sBuff;

    return 1;
}