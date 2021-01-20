#include "../../Status.h"
#include <iostream>
using namespace std;

typedef struct
{
  float coef; // 多项式系数
  int expm;   // 多项式指数
} ElemType;   // 重新定义扩展的线性表中元素类型
typedef struct LNode
{
  ElemType data;
  struct LNode *next;
} LNode, *Link, *Position;
typedef struct
{
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

Status LocatePos(ELinkList L, int i, Link *cur);

Status InsFirst(ELinkList *L, Link pre, Link cur);

Status DelFirst(ELinkList *L, Link pre, Link *cur);

Status LocateElem(ELinkList L, ElemType e, Position *q, Status(Compare)(ElemType, ElemType));

/*
 * 取值
 *
 * 获取结点p的元素值。
 */
ElemType GetCurElem(Link p);

/*
 * 设值
 *
 * 为结点p设置元素值。
 */
Status SetCurElem(Link p, ElemType e);

/*
 * 头结点
 *
 * 获取头结点引用。
 */
Position GetHead(ELinkList L);

/*
 * 后继
 *
 * 获取结点p的后继，如果不存在，则返NULL。
 */
Position NextPos(ELinkList L, Link p);

/*
 * 向尾部添加
 *
 * 将s所指的一串结点链接在链表L后面
 */
Status Append(ELinkList *L, Link s);