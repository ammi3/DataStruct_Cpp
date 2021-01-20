#include "../../Status.h"
#include <iostream>
using namespace std;

typedef int ElemType;
typedef struct LNode
{
  ElemType data;      // 数据结点
  struct LNode *next; // 指向下一个结点的指针
} LNode;
// 指向单链表结点的指针
typedef LNode *LinkList;

// 初始化
Status InitList(LinkList *L);

// 摧毁单链表
Status DestoryList(LinkList *L);

// 清空
Status ClearList(LinkList *L);

// 判断是否为空
Status ListEmpty(LinkList L);

// 计数
Status ListLength(LinkList L);

// 取值
Status GetElem(LinkList L, int i, ElemType *e);

// 插入
Status ListInsert(LinkList L, int i, ElemType e);

// 删除
Status ListDelete(LinkList L, int i, ElemType *e);

// 遍历
void ListTraverse(LinkList L);

// 头插法创建链表
Status CreateList_Head(LinkList *L, int n);

// 尾插法创建链表
Status CreateList_Tail(LinkList *L, int n);
