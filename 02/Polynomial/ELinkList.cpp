#include "ELinkList.h"

// 内存分配
Status MakeNode(Link *p, ElemType e)
{
  if (p == NULL)
    return ERROR;
  *p = (Link)malloc(sizeof(LNode));
  if (*p == NULL)
    return ERROR;
  (*p)->data = e;
  (*p)->next = NULL;
  return OK;
}

// 内存回收
void FreeNode(Link *p)
{
  if (p == NULL || *p == NULL)
    return;
  free(*p);
  *p = NULL;
}

// 初始化
Status InitList(ELinkList *L)
{
  if (L == NULL)
    return ERROR;
  Link p = (Link)malloc(sizeof(LNode));
  if (p == NULL)
    return ERROR;
  p->next = NULL;
  (*L).head = (*L).tail = p;
  (*L).len = 0;
  return OK;
}

// 销毁
Status DestoryList(ELinkList *L)
{
  if (L == NULL || (*L).head == NULL)
    return ERROR;
  ClearList(L);
  free((*L).head);
  (*L).head = (*L).tail = NULL;
  return OK;
}

// 清空
Status ClearList(ELinkList *L)
{
  if (L == NULL || (*L).head == NULL || (*L).len < 0)
    return ERROR;
  Link cur = (*L).head->next;
  Link next;
  while (cur != NULL)
  {
    next = cur->next;
    free(cur);
    cur = next;
  }
  (*L).head->next = NULL;
  (*L).tail = (*L).head;
  (*L).len = 0;
  return OK;
}

// 判断是否为空
Status ListEmpty(ELinkList L)
{
  if (L.len <= 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// 计数
int ListLength(ELinkList L)
{
  return L.len;
}

Status LocateElem(ELinkList L, ElemType e, Position *q, Status(Compare)(ElemType, ElemType))
{
  Position pre, p;

  *q = NULL;

  // 链表不存在，返回错误信息
  if (L.head == NULL)
  {
    return FALSE;
  }

  pre = L.head;
  p = pre->next;

  while (p != NULL && Compare(p->data, e) < 0)
  {
    pre = p;
    p = p->next;
  }

  // 找到了与e满足"相等"条件的元素
  if (p != NULL && Compare(p->data, e) == 0)
  {
    *q = p;
    return TRUE;
  }

  // 所有元素均小于e，或者p元素大于e，又或者为空表
  *q = pre;

  return FALSE;
}

// 查找
Status LocatePos(ELinkList L, int i, Link *cur)
{
  if (i < 0 || i > L.len)
    return ERROR;
  if (L.head == NULL)
    return ERROR;
  if (i == 0)
  {
    *cur = L.head;
    return OK;
  }
  int count = 0;
  Link pre = L.head;
  while (pre != NULL && count < i)
  {
    count++;
    pre = pre->next;
  }
  if (pre == NULL)
    return ERROR;
  *cur = pre;
  return OK;
}

// 插入
Status InsFirst(ELinkList *L, Link pre, Link cur)
{
  if (L == NULL || (*L).head == NULL || pre == NULL || cur == NULL)
    return ERROR;
  cur->next = pre->next;
  pre->next = cur;

  if (pre == (*L).tail)
    (*L).tail = pre->next;
  (*L).len++;
  return OK;
}

// 删除---删除pre结点后的第一个结点，并用cur来存储被删除的结点
Status DelFirst(ELinkList *L, Link pre, Link *cur)
{
  if (L == NULL || (*L).head == NULL || pre == NULL || cur == NULL)
    return ERROR;
  if (pre->next == NULL)
    return ERROR;
  *cur = pre->next;
  pre->next = (*cur)->next;
  (*cur)->next = NULL;
  if (pre->next == NULL)
    (*L).tail = pre;
  (*L).len--;
  return OK;
}

/*
 * 取值
 *
 * 获取结点p的元素值。
 */
ElemType GetCurElem(Link p)
{
  ElemType e;

  if (p == NULL)
  {
    e.coef = 0.0f;
    e.expm = -1;
    return e;
  }

  return p->data;
}

/*
 * 设值
 *
 * 为结点p设置元素值。
 */
Status SetCurElem(Link p, ElemType e)
{
  if (p == NULL)
  {
    return ERROR;
  }

  p->data = e;

  return OK;
}

/*
 * 头结点
 *
 * 获取头结点引用。
 */
Position GetHead(ELinkList L)
{
  return L.head;
}

/*
 * 后继
 *
 * 获取结点p的后继，如果不存在，则返NULL。
 */
Position NextPos(ELinkList L, Link p)
{

  // 确保链表(头结点)存在
  if (L.head == NULL)
  {
    return NULL;
  }

  if (p == NULL)
  {
    return NULL;
  }

  return p->next;
}

/*
 * 向尾部添加
 *
 * 将s所指的一串结点链接在链表L后面
 */
Status Append(ELinkList *L, Link s)
{
  int count;

  if (L == NULL || (*L).head == NULL || s == NULL)
  {
    return ERROR;
  }

  count = 0;
  (*L).tail->next = s;

  // 确定新的尾结点位置
  while (s != NULL)
  {
    (*L).tail = s;
    s = s->next;
    count++;
  }

  (*L).len += count;

  return OK;
}
