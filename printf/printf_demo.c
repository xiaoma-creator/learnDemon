/******************************************************************************

                  版权所有 (C), 2018-2099, yinwenfeng

 ******************************************************************************
  文 件 名   : printf_demo.c
  版 本 号   : 初稿
  作    者   : yinwenfeng
  生成日期   : 2022年3月31日
  最近修改   :
  功能描述   : printf带颜色输出
  
  修改历史   :
  1.日    期   : 2022年3月31日
    作    者   : yinwenfeng
    修改内容   : 创建文件

******************************************************************************/

#include <stdio.h>

/*
	格式：printf("\033[背景颜色;字体颜色m字符串\033[0m\n);
	
	部分颜色代码:
	字背景颜色: 40--49                字颜色: 30--39
	40: 黑                           30: 黑
	41: 红                           31: 红
	42: 绿                           32: 绿
	43: 黄                           33: 黄
	44: 蓝                           34: 蓝
	45: 紫                           35: 紫
	46: 深绿                         36: 深绿
	47：白色                         37：白色
	————————————————
	版权声明：本文为CSDN博主「ericbars」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
	原文链接：https://blog.csdn.net/ericbar/article/details/79652086

	通用格式控制:
    0 重置所有属性
    1 高亮/加粗
    2 暗淡
    4 下划线
    5 闪烁
    7 反转
    8 隐藏
*/

/* 需要在linux下运行 */
int main()
{
	printf("\033[47;32mhello\033[0m\n"); //白底绿字
	printf("\033[47;30mhello\033[0m\n"); //白底黑字
	printf("\033[47;33mhello\033[0m\n");
	printf("\033[47;34mhello\033[0m\n");
	printf("\033[47;35mhello\033[0m\n");
	printf("\033[47;36mhello\033[0m\n");
	printf("\033[47;35m[%s, %d]:\033[0m \n", __FUNCTION__, __LINE__);
    printf("\033[1;35m[%s, %d]:\033[0m \n", __FUNCTION__, __LINE__);

    return 1;
}

