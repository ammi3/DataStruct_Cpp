#include "../../Status.h"
#include <iostream>
#include <string.h>
using namespace std;

#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN + 1];

// 初始化
Status StrAssign(SString T, const char *chars);

// 销毁
Status DestoryString(SString S);

// 清空
Status ClearString(SString S);

// 判空
Status StrEmpty(SString S);

// 计数
int StrLength(SString S);

// 求子串
Status SubString(SString Sub, SString S, int pos, int len);

// 查找---此实现需要依赖串的最小操作子集
int Index_1(SString S, SString T, int pos);

// 查找
int Index_2(SString S, SString T, int pos);

// 插入
Status StrInsert(SString S, int pos, SString T);

// 删除
Status StrDelete(SString S, int pos, int len);

// 比较
int StrCompare(SString S, SString T);

// 复制
Status StrCopy(SString T, SString S);

// 替换
Status Replace(SString S, SString T, SString V);

// 串连接
Status Concat(SString T, SString S1, SString S2);