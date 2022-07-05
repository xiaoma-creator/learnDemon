#include <stdio.h>

#define NDEBUG //定义此宏assert失效，需定义再#include <assert.h>前
#include <assert.h>



int main(int argc, char const *argv[])
{
    int i = 1;

    assert(0 == i); //判断i == 0 ，为真继续执行程序，为假报告错误信息，并退出程序 
    printf("hello assert\n");
    
    return 0;
}
