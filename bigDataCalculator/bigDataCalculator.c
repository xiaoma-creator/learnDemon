#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//大数据结构体
typedef struct BIG_DATA_STRU
{
    int lenth;      //数据长度
    char data[];    //数据内容，data[0]个位，data[1]十位，data[2]百位...
}BIG_DATA;

/*
void print_big_data(BIG_DATA *num)
{
    int i;

    if (NULL == num)
    {
        printf("[---ywf---%d, %s]: num is null\n", __LINE__, __FUNCTION__);
        return;
    }

    for (i = 0; i < num->lenth; i++)
    {
        printf("%d", num->data[i]);
    }
}

void str_to_big_data(char *str, BIG_DATA *num)
{
    int i = 0;
    int len = 0;

    if (NULL == str)
    {
        printf("[---ywf---%d, %s]: str is null\n", __LINE__, __FUNCTION__);
        return;
    }

    if (NULL == num)
    {
        printf("[---ywf---%d, %s]: num is null\n", __LINE__, __FUNCTION__);
        return;
    }

    len = strlen(str);
    num = malloc(sizeof(BIG_DATA) + len);

    for (i = 0; i < len; i++)
    {
        if (isdigit(str[i]))
        {
            
        }
        else 
        {
            printf("[---ywf---%d, %s]: str[%d] is not digit\n", __LINE__, __FUNCTION__, i);
            return;
        }
    }
    
}
*/

int main(int argc, char const *argv[])
{
    char str[256] = {0}; //计算式
    char *p;
    BIG_DATA num;

    scanf("%s", str);
    printf("[---ywf---%d, %s]: \n", __LINE__, __FUNCTION__);


    printf("%d", sizeof(BIG_DATA));
    return 0;
}
