#include "../../Status.h"
#include <iostream>
using namespace std;

typedef enum
{
  Arrive,
  Leave_1,
  Leave_2,
  Leave_3,
  Leave_4
} EventType;

/* 事件链表元素类型定义 */
typedef struct
{
  int OccurTime;   // 事件发生时刻
  EventType NType; // 事件类型
} Event, ElemType; // 事件链表元素

/*
 * 单链表结构
 *
 * 注：这里的单链表存在头结点
 */
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
