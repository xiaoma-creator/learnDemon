// #define _DEFAULT_SOURCE     // 加上这个宏定义
// #define _BSD_SOURCE         // 如果是比较老的内核的话则用这个宏定义
#include <stdio.h>  
#include <unistd.h>  
 
/*
    #include <unistd.h>
    原型：int deamon(int onchdir, int noclose);
    参数：nochdir为0，表示将更改进程的目录为根目录'/'，否则（非0）时保持当前执行目录不变。
          noclose为0，会将标准输入(0)，标准输出(1)，标准错误(2)重定向到/dev/null，
            否则保持原有标准输入(0)，标准输出(1)，标准错误(2)不变。
    返回值：0:成功 -1：错误
    注意：如果noclose值为0，需要确保0，1，2三个fd没有用于打开其他文件。
*/

int main(int argc, char const *argv[])
{
    int a;

    // if(-1 == deamon(1, 1))
    // {
    //     printf("deamon error:%s", stderr);
    //     return -1;
    // }

    // while(1)
    // {
    //     printf("hello\n");
    //     sleep(1);
    // }

    printf("你好\n");
    return 0;
}
