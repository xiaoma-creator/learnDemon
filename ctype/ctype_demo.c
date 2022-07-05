#include <stdio.h>
#include <ctype.h>

/*
    int isalnum(int c) //判断是否为字母或数； 返回值：0：不是 非0：是
    int isalpha(int c) //判断是否为字母；返回值：0：不是 非0：是
*/

int main(int argc, char const *argv[])
{
    int ch = 'a';

    /* 判断是否为字母或数字 */
    if (isalnum(ch))
    {
        printf("%c is an alphabate or a number\n", ch);
    }
    else
    {
        printf("%c is not an alphabate or a number\n", ch);
    }

    /* 判断是否为字母 */
    if (isalpha(ch))
    {
        printf("%c is an alphabate\n", ch);
    }
    else 
    {
        printf("%c is not an alphabate\n", ch);
    }

    /* 判断是否为数字 */
    if (isdigit(ch))
    {
        printf("%c is a digital\n", ch);
    }
    else 
    {
        printf("%c is not a digital\n", ch);
    }

    /*  
        判断是否为控制字符
        ASCII码中，第0~31号和127号是控制字符
        也就是'\n' '\t' '\a'这些,'\a'是响铃字符，输出这个字符时，电脑会嘟~一声^_^
    */
    if (iscntrl(ch))
    {
        printf("%c is contrl character\n", ch);
    }
    else 
    {
        printf("%c is not contrl character\n", ch);
    }

    /* 
        判断是否有图形表示法
        所有可打印的字符，都是有图形表示法
    */
    if (isgraph(ch))
    {
        printf("%c is a graph\n", ch);
    }
    else 
    {
        printf("%c is not a graph\n", ch);
    }

    /* 判断是否为小写 */
    if (islower(ch))
    {
        printf("%c is lower\n", ch);
    }
    else 
    {
        printf("%c is not lower\n", ch);
    }

    /* 判断是否为大写 */
    if (isupper(ch))
    {
        printf("%c is upper\n", ch);
    }
    else 
    {
        printf("%c is not upper\n", ch);
    }

    /* 判断是否能打印 */
    if (isprint(ch))
    {
        printf("%c is print\n", ch);
    }
    else 
    {
        printf("%c is not print\n", ch);
    }

    /* 判断是否能打印 */
    if (isprint(ch))
    {
        printf("%c is print\n", ch);
    }
    else 
    {
        printf("%c is not print\n", ch);
    }

    /* 
        判断是否是标点符号 
        ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~ 
    */
    if (ispunct(ch))
    {
        printf("%c is print\n", ch);
    }
    else 
    {
        printf("%c is not print\n", ch);
    }

    return 0;
}
