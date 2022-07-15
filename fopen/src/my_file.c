#include "my_file.h"

/*****************************************************************************
*  函 数 名：read_line_from_tail
*  功能描述：从文件末尾读取 iTargetLine 行
*  输入参数：pSFile 文件指针
            iTargetLine 需要读取的行数          
*  输出参数：ppDest 存储位置
*  返 回 值：0：失败
            1：成功
            2：空文件

*****************************************************************************/
int read_line_from_tail(FILE *pFile, int iTargetLine, char **ppDest)
{
    char cCh = 0;
    char szLine[512] = {0};
    char *sBuff = NULL;
    char *psMoreMemory = NULL;
    char cFlagFirstChar = 1;
    char cFlagFirstLine = 1;
    unsigned long ulBuffSize = 0;
    long lIndex = 0;
    long lFileIndex = 0;
    int iLineCnt = 0;

    if (pFile == NULL || iTargetLine <= 0)
    {
        return 0;
    }

    /* 空文件 */
    if (fgetc(pFile) == EOF)
    {
        return 2;
    }

    lIndex = -1;
    while(iLineCnt < iTargetLine)
    {
        fseek(pFile, lIndex, SEEK_END);
        lFileIndex = ftell(pFile);
        cCh = fgetc(pFile);

        /* 遇到\n 或者已经是文件第一行，读取一行 */
        if (lFileIndex == 0 || cCh == '\n')
        {
            /* 文件末尾的换行符 */
            if (cFlagFirstChar && lFileIndex != 0) 
            {
                cFlagFirstChar = 0;
                lIndex--;
                continue;
            }

            if (lFileIndex == 0)
            { 
                fseek(pFile, lFileIndex, SEEK_SET); //文件第一行，从最开始读
            }

            fgets(szLine, sizeof(szLine), pFile); 
            for (int i = 0; i < strlen(szLine); i++)
            {
                if ('<' == szLine[i] || '>' == szLine[i] || '&' == szLine[i] \
                    || '\"' == szLine[i] || '\'' == szLine[i] )
                {
                    szLine[i] = ' ';
                }
            }  

            ulBuffSize += strlen(szLine);           //记录总大小
            psMoreMemory = (char *)realloc(sBuff, ulBuffSize+1); //重新分配内存
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
            /* 将新读取的一行拷贝的新内存 */
            memcpy(sBuff+ulBuffSize-strlen(szLine), szLine, strlen(szLine)); 
            sBuff[ulBuffSize] = '\0';

            if (cFlagFirstLine)
            {
                cFlagFirstLine = 0;
                if (sBuff[ulBuffSize-1] != '\n')
                {
                    sBuff[ulBuffSize] = '\n';
                    ulBuffSize++;
                    psMoreMemory = (char *)realloc(sBuff, ulBuffSize+1); //重新分配内存
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
                    sBuff[ulBuffSize] = '\0';
                }
            }

            iLineCnt++;
            if (lFileIndex == 0)
            {
                break;
            }
            
        }

        cFlagFirstChar = 0;
        lIndex--;    
    }

    // if (sBuff == NULL)
    // {
    //     sBuff = (char *)malloc(1);
    //     sBuff[0] = '\0';
    // }

    *ppDest = sBuff;

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


void split(char *src,const char *separator,char **dest,int *num) {
	/*
		src 源字符串的首地址(buf的地址) 
		separator 指定的分割字符
		dest 接收子字符串的数组
		num 分割后子字符串的个数
	*/
     char *pNext;
     int count = 0;
     if (src == NULL || strlen(src) == 0) //如果传入的地址为空或长度为0，直接终止 
        return;
     if (separator == NULL || strlen(separator) == 0) //如未指定分割的字符串，直接终止 
        return;
     pNext = (char *)strtok(src,separator); //必须使用(char *)进行强制类型转换(虽然不写有的编译器中不会出现指针错误)
     while(pNext != NULL) {
          *dest++ = pNext;
          ++count;
         pNext = (char *)strtok(NULL,separator);  //必须使用(char *)进行强制类型转换
    }  
    *num = count;
}

