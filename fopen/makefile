#makefile注释

TARGET=a.out
OBJ=demon_fopen.o
SOURCE_FILE=$(wildcard %.c)


$(TARGET):$(OBJ)
	gcc -o $@ $^


%.o:%.c
	gcc -c $^ -o $@

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
	
