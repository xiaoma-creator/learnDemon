#include <stdio.h>
#include <unistd.h>

/*
头文件 #include <unistd.h>

int getopt(int argc, char * const argv[], const char *optstring);
getopt 参数说明：
    argc：通常由 main 函数直接传入，表示参数的数量
    argv：通常也由 main 函数直接传入，表示参数的字符串变量数组
    optstring：一个包含正确的参数选项字符串，用于参数的解析。
                例如 “abc:”，其中 -a，-b 就表示两个普通选项，-c 表示一个必须有参数的选项，因为它后面有一个冒号
外部变量说明：
    optarg：如果某个选项有参数，这包含当前选项的参数字符串
    optind：argv 的当前索引值
    opterr：正常运行状态下为 0。非零时表示存在无效选项或者缺少选项参数，并输出其错误信息
    optopt：当发现无效选项字符时，即 getopt() 方法返回 ? 字符，optopt 中包含的就是发现的无效选项字符
————————————————
版权声明：本文为CSDN博主「阿飞__」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/afei__/article/details/81261879

*/

/*
    使用说明
*/
static const char usage[] = 
"Usage:\n"
"    main [-h] [-t] [-a message]\n"
"\n"
"    -h display this help screen\n"
"    -t test\n"
"    -a add message\n";

int main(int argc, char const *argv[])
{
    
    char ch = 0;
    // opterr = 0; //不打印错误信息

    while ( (ch = getopt(argc, argv, "hta:")) != -1)
    {
        switch (ch)
        {
        case 'h':
            printf("option %s: --help;  argument: %s\n", argv[optind-1], optarg);
            printf("%s", usage);
            break;
        case 't':
            printf("option %s: --test;  argument: %s\n", argv[optind-1], optarg);
            break;
        case 'a':
            printf("option %s: --add;  argument: %s\n", argv[optind-1], optarg);
            break;
        case '?':
            // printf("invalid option\n");
            printf("%s", usage);
            break;
        default:
            break;
        }
    }

    return 0;
}
