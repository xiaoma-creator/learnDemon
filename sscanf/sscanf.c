#include <stdio.h>
#include <stdlib.h> //atoi

/*

*：可选*号，表示被忽略，不存储到对应的参数中。

*/

int main(int argc, char const *argv[])
{
    char up_connection[4] = {0};
    char on_connection[4] = {0};
    const char *str1 = "1 up, 0 conneting):";

    sscanf(str1, "%s %*s %s %*s", up_connection, on_connection);
    printf("up_connection: %s\non_connection: %s\n", up_connection, on_connection);
    /*输出结果：
        up_connection: 1
        on_connection: 0
    */
    int up = atoi(up_connection);
    int on = atoi(on_connection);
    printf("up = %d, on = %d\n", up, on);
    /*输出结果：
        up: 1
        on: 0
    */ 
    const char *str2 = "172.5.5.3[www.qqqqqqqqqqqqqqqqqqqqqqqq.com]...176.5.5.3[www.qqqqqqqqqqqqqqqqqqqqqqqw.com]";
    char startip[64] = {0};
    char destip[64] = {0};

    /*
        %*:忽略
        %*[^[]]:忽略--直到匹配[
        %[^]]:选择--直到匹配]
    */
    sscanf(str2, "%*[^[]\[%[^]]%*[^[]\[%[^]]", startip, destip);
    printf("starip: %s\nsestip: %s\n", startip, destip);
    /*
    输出结果：
        starip: www.qqqqqqqqqqqqqqqqqqqqqqqq.com
        sestip: www.qqqqqqqqqqqqqqqqqqqqqqqw.com
    */
    return 0;
}


