#include <stdio.h>
#include <ctype.h>

/*
    int isalnum(int c) //�ж��Ƿ�Ϊ��ĸ������ ����ֵ��0������ ��0����
    int isalpha(int c) //�ж��Ƿ�Ϊ��ĸ������ֵ��0������ ��0����
*/

int main(int argc, char const *argv[])
{
    int ch = 'a';

    /* �ж��Ƿ�Ϊ��ĸ������ */
    if (isalnum(ch))
    {
        printf("%c is an alphabate or a number\n", ch);
    }
    else
    {
        printf("%c is not an alphabate or a number\n", ch);
    }

    /* �ж��Ƿ�Ϊ��ĸ */
    if (isalpha(ch))
    {
        printf("%c is an alphabate\n", ch);
    }
    else 
    {
        printf("%c is not an alphabate\n", ch);
    }

    /* �ж��Ƿ�Ϊ���� */
    if (isdigit(ch))
    {
        printf("%c is a digital\n", ch);
    }
    else 
    {
        printf("%c is not a digital\n", ch);
    }

    /*  
        �ж��Ƿ�Ϊ�����ַ�
        ASCII���У���0~31�ź�127���ǿ����ַ�
        Ҳ����'\n' '\t' '\a'��Щ,'\a'�������ַ����������ַ�ʱ�����Ի��~һ��^_^
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
        �ж��Ƿ���ͼ�α�ʾ��
        ���пɴ�ӡ���ַ���������ͼ�α�ʾ��
    */
    if (isgraph(ch))
    {
        printf("%c is a graph\n", ch);
    }
    else 
    {
        printf("%c is not a graph\n", ch);
    }

    /* �ж��Ƿ�ΪСд */
    if (islower(ch))
    {
        printf("%c is lower\n", ch);
    }
    else 
    {
        printf("%c is not lower\n", ch);
    }

    /* �ж��Ƿ�Ϊ��д */
    if (isupper(ch))
    {
        printf("%c is upper\n", ch);
    }
    else 
    {
        printf("%c is not upper\n", ch);
    }

    /* �ж��Ƿ��ܴ�ӡ */
    if (isprint(ch))
    {
        printf("%c is print\n", ch);
    }
    else 
    {
        printf("%c is not print\n", ch);
    }

    /* �ж��Ƿ��ܴ�ӡ */
    if (isprint(ch))
    {
        printf("%c is print\n", ch);
    }
    else 
    {
        printf("%c is not print\n", ch);
    }

    /* 
        �ж��Ƿ��Ǳ����� 
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
