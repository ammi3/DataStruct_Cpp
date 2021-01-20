#include "../../Status.h"
#include <iostream>
using namespace std;

typedef int ElemType;
typedef struct LNode
{
  ElemType data;
  struct LNode *next;
}LNode, *Link, *Position;
typedef struct {
  Link head, tail;
  int len;
} ELinkList;

// 内存分配
Status MakeNode(Link *p, ElemType e);

// 内存回收
void FreeNode(Link *p);

// 初始化
Status InitList(ELinkList *L);

// 销毁
Status DestoryList(ELinkList *L);

// 清空
Status ClearList(ELinkList *L);

// 判空
Status ListEmpty(ELinkList L);

// 计数
int ListLength(ELinkList L);

// 插入
Status ListInsert(ELinkList *L, int i, ElemType *e);

// 删除
Status ListDelete(ELinkList *L, int i, ElemType *e);

// 遍历
void ListTraverse(ELinkList L);

Status LocatePos(ELinkList L, int i, Link *cur);

Status InsFirst(ELinkList *L, Link pre, Link cur);

Status DelFirst(ELinkList *L, Link pre, Link *cur);