#include <stdio.h>
// 函数结果状态码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

int ReadData(FILE *fp, char *format, ...);

void Wait(long time);