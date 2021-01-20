#include "../../Status.h"
#include <iostream>
using namespace std;

#define MAXSIZE 100

typedef int ElemType;
typedef struct SLinkNode
{
  ElemType data;
  int cur; // 表示相对位置
} SLinkList[MAXSIZE];

// 初始化空间
void InitSpace(SLinkNode space);

// 申请空间
int Malloc(SLinkNode space);

// 回收空间
void Free(SLinkNode space, int k);

// 初始化
Status InitList(SLinkNode space, int *S);

// 销毁
Status DestoryList(SLinkNode space, int *S);

// 置空
Status ClearList(SLinkNode space, int S);

// 判空
Status ListEmpty(SLinkNode space, int S);

// 计数
Status ListLength(SLinkNode space, int S);

// 取值
Status GetElem(SLinkNode space, int S, int i, ElemType *e);

// 插入
Status ListInsert(SLinkNode space, int S, int i, ElemType e);

// 删除
Status ListDelete(SLinkNode space, int S, int i, ElemType *e);

// 遍历
Status ListTraverse(SLinkNode space, int S);

// 表示 (A-B)∪(B-A)
void difference(SLinkList space, int *S);