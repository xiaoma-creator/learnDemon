#makefile注释

#makefile 环境变量，指定搜索路径
VPATH:=src obj

#include path
INCLUDE:=inc

TARGET=a.out
OBJ=main.o my_file.o

SOURCE_FILE=$(wildcard *.c) #扩展 *.c 否则使用$(SOURCE_FILE)时会认为*.c是文件名


$(TARGET):$(OBJ)
	gcc -o $@ $^

%.o:%.c
	gcc -c $^ -o $@ -I $(INCLUDE)

clean:
	rm -fr *.o a.out *.exe




#makefile变量赋值
#:= 当前语句赋值
#=	递归赋值
#?= 如果变量未定义，则用该值定义变量，否则该语句无效
#+= 追加赋值，原变量用空格隔开的方式追加一个新值
x:=foo
y:=${x}b
x:=new

test:
	@echo "y=${y}"
	@echo "x=${x}"
	
