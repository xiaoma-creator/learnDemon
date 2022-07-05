#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *str1 = "192.168.10.5";
    char *str2 = "192.168.10.1";

    char *res = strstr(str1, str2);
    if (NULL == res)
    {
        printf("null\n");
    }
    else
    {
        printf("res = %s\n", res);
    }


    return 0;
}
