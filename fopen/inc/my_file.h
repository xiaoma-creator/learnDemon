#ifndef __MY_FILE_H__
#define __MY_FILE_H__

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

extern int read_file_by_line(const char *sFileName, char **pcDst);
extern int read_line_from_tail(FILE *pFile, int iTargetLine, char **ppDest);

#endif
