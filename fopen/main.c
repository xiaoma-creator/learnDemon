#include "my_file.h"

#define FILE_KEY_MESSAGE    ("./keymessage.log")
#define FILE_MESSAGE        ("./message.log")
#define FILE_EMPTY          ("./empty.txt")


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
    FILE *pFile = NULL;
    int iResult = 0;

    pFile = fopen(FILE_EMPTY, "r");
    if (NULL == pFile)
    {
        printf("fopen file %s error: %s", FILE_EMPTY, strerror(errno));
        return -1;
    }

    iResult = read_line_from_tail(pFile, 1000, &sContent);
    if (0 == iResult)
    {
        printf("read line from tail fail\n");
    }
    else if (2 == iResult)
    {
        printf("empty file\n");
    }
    else if (1 == iResult)
    {
        printf("%s", sContent);
    }

    if (NULL != sContent)
    {
        free(sContent);
        sContent = NULL;
    }

    return 0;
}