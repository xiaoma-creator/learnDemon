#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define FILEPATH ("./test.txt")

int main(int argc, char const *argv[])
{
	char *buff = NULL;
	unsigned long buffSize = 0;
	char line[512] = {0};
	
	
    FILE *file = fopen(FILEPATH, "r");
	if (!file)
	{
		printf("can not open %s: %s\n", FILEPATH, strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* 一个字符读取 */
//	char ch = fgetc(file);
//	while( EOF != ch)
//	{
//		buffSize++;
//		buff = (char *)realloc(buff, buffSize);
//		buff[buffSize-1] = ch;
//		ch = fgetc(file);
//	}
//	buff[buffSize] = '\0';
//	printf("%s", buff);
//	free(buff);

	/* 一次读取一行 */
	fseek(file, 0, SEEK_SET);
	while (NULL != fgets(line, sizeof(line), file))
	{
		buffSize += strlen(line);
		buff = (char *)realloc(buff, buffSize);
		
		strcat(buff, line);
	}
	printf("%s", buff);
	free(buff);
	fclose(file);

	printf("\r\n \033[1;35m[--ywf--]func: %s, line: %d\033[0m: file size %fkb\n", __FUNCTION__, __LINE__, buffSize/1024.0);
    return 0;
}

