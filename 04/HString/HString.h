#include "../../Status.h"
#include <iostream>
#include <string.h>
using namespace std;

typedef struct
{
  char *ch; //若是非空串，则按串长分配存储区
  int length;
} HString;

// 初始化
Status StrAssign(HString *T, const char *chars);

// 销毁
Status DestoryString(HString *S);

// 清空
Status ClearString(HString *S);

// 判空
Status StrEmpty(HString S);

// 计数
int StrLength(HString S);

// 求子串
Status SubString(HString *Sub, HString S, int pos, int len);

// 查找---此实现需要依赖串的最小操作子集
int Index(HString S, HString T, int pos);

// 插入
Status StrInsert(HString *S, int pos, HString T);

// 删除
Status StrDelete(HString *S, int pos, int len);

// 比较
int StrCompare(HString S, HString T);

// 复制
Status StrCopy(HString *T, HString S);

// 替换
Status Replace(HString *S, HString T, HString V);

// 串连接
Status Concat(HString *T, HString S1, HString S2);