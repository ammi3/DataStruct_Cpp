#include "../../Status.h"
#include <iostream>
using namespace std;

typedef int ElemType;
typedef struct DuLNode
{
  ElemType data;
  struct DuLNode *prior; // 前驱
  struct DuLNode *next;  // 后继
} DuLNode;
typedef DuLNode *DuLinkList;

// 初始化
Status InitList(DuLinkList *L);

// 销毁
Status DestoryList(DuLinkList *L);

// 置空
Status ClearList(DuLinkList L);

// 判空
Status ListEmpty(DuLinkList L);

// 计数
int ListLength(DuLinkList L);

// 取值
Status GetElem(DuLinkList L, int i, ElemType *e);

// 插入
Status ListInsert(DuLinkList L, int i, ElemType e);

// 删除
Status ListDelete(DuLinkList L, int i, ElemType *e);

// 遍历
void ListTraverse(DuLinkList L);

static DuLinkList GetElemP(DuLinkList L, int i);