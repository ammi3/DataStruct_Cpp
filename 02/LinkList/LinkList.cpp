#include "LinkList.h"

/**
 * 初始化链表
 */
Status InitList(LinkList *L)
{
  (*L) = (LinkList)malloc(sizeof(LNode));
  if (*L == NULL)
    return ERROR;
  (*L)->next = NULL;
  return OK;
}

/**
 * 摧毁单链表
 */
Status DestoryList(LinkList *L)
{
  if (L == NULL || *L == NULL)
    return ERROR;
  LinkList p = *L;
  while (p != NULL)
  {
    p = (*L)->next;
    free(*L);
    (*L) = p;
  }
  *L = NULL;
  return OK;
}

/**
 * 清空
 */
Status ClearList(LinkList L)
{
  if (L == NULL)
    return ERROR;
  LinkList pre;
  LinkList p = L->next;
  while (p != NULL)
  {
    pre = p;
    p = p->next;
    free(pre);
  }
  L->next = NULL;
  return OK;
}

/**
 * 判断是否为空
 */
Status ListEmpty(LinkList L)
{
  if (L != NULL && L->next == NULL)
    return true;
  else
    return false;
}

/**
 * 计数
 */
Status ListLength(LinkList L)
{
  if (L == NULL || L->next == NULL)
    return ERROR;
  int i = 0;
  LinkList p = L->next;
  while (p != NULL)
  {
    i++;
    p = p->next;
  }
  return i;
}

/**
 * 取值
 */
Status GetElem(LinkList L, int i, ElemType *e)
{
  if (L == NULL || L->next == NULL)
    return ERROR;
  int j = 0;
  LinkList p = L;
  while (p->next != NULL && j < i - 1)
  {
    p = p->next;
    ++j;
  }
  if (p->next == NULL || j > i - 1)
    return ERROR;
  *e = p->next->data;
  return OK;
}

/**
 * 插入
 */
Status ListInsert(LinkList L, int i, ElemType e)
{
  if (L == NULL)
    return ERROR;
  int j = 0;
  LinkList p = L;
  while (p != NULL && j < i - 1)
  {
    p = p->next;
    ++j;
  }
  if (p == NULL || j > i - 1)
    return ERROR;
  LinkList s = (LinkList)malloc(sizeof(LNode));
  if (s == NULL)
    return ERROR;
  s->data = e;
  s->next = p->next;
  p->next = s;
  return OK;
}

/**
 * 删除
 */
Status ListDelete(LinkList L, int i, ElemType *e)
{
  if (L == NULL)
    return ERROR;
  int j = 0;
  LinkList p = L;
  while (p->next != NULL && j < i - 1)
  {
    p = p->next;
    ++j;
  }
  if (p->next == NULL || j > i - 1)
    return ERROR;
  LinkList q = p->next;
  p->next = q->next;
  *e = q->data;
  free(q);
  return OK;
}

/**
 * 遍历
 */
void ListTraverse(LinkList L)
{
  if (L == NULL || L->next == NULL)
    return;
  LinkList p = L->next;
  while (p != NULL)
  {
    cout << p->data << " ";
    p = p->next;
  }
  cout << endl;
}

Status createList_Head(LinkList *L, int n)
{
  *L = (LinkList)malloc(sizeof(LNode));
  (*L)->next = NULL;

  LinkList cur;
  for (int i = 1; i <= n; i++)
  {
    cur = (LinkList)malloc(sizeof(LNode));
    printf("请输入第%d个元素的值：", i);
    scanf("%d", &(cur->data));
    cur->next = (*L)->next;
    (*L)->next = cur;
  }
  return OK;
}

/**
 尾插法建立链表
 */
Status createList_Tail(LinkList *L, int n)
{
  *L = (LinkList)malloc(sizeof(LNode));
  (*L)->next = NULL;
  LinkList cur, pre = *L;
  for (int i = 1; i <= n; i++)
  {
    cur = (LinkList)malloc(sizeof(LNode));
    printf("请输入第%d个元素的值：", i);
    scanf("%d", &(cur->data));
    pre->next = cur;
    pre = pre->next;
  }
  pre->next = NULL;
  return OK;
}

/**
 * 合并链表
 */
void MergeList(LinkList *L1, LinkList *L2, LinkList *L3)
{
  LinkList cur1 = (*L1)->next, cur2 = (*L2)->next;
  LinkList cur = *L3 = *L1;
  while (cur1 != NULL && cur2 != NULL)
  {
    if (cur1->data <= cur2->data)
    {
      cur->next = cur1;
      cur = cur1;
      cur1 = cur1->next;
    }
    else
    {
      cur->next = cur2;
      cur = cur2;
      cur2 = cur2->next;
    }
  }

  cur->next = cur1 ? cur1 : cur2;
}

int main()
{
  LinkList L;
  int i;
  ElemType e;
  cout << "开始初始化单链表" << endl;
  InitList(&L);
  cout << "单链表初始化成功" << endl;
  cout << "开始插入元素" << endl;
  for (i = 1; i <= 9; i++)
  {
    printf("在 L 第 %d 个位置插入 \"%d\" ...\n", i, i);
    ListInsert(L, i, i);
  }
  cout << "插入元素结束" << endl;
  int length = ListLength(L);
  cout << "该单链表的长度为：" << length << endl;
  printf("该单链表内元素为：");
  ListTraverse(L);

  LinkList L1;
  cout << "开始头插法创建单链表" << endl;
  createList_Head(&L1, 5);
  cout << "头插法创建链表结束" << endl;
  cout << "该链表的元素依次为：";
  ListTraverse(L1);

  LinkList L2;
  cout << "开始尾插法创建单链表" << endl;
  createList_Tail(&L2, 5);
  cout << "尾插法创建链表结束" << endl;
  cout << "该链表的元素依次为：";
  ListTraverse(L2);

  LinkList L3;
  cout << "开始合并两个链表" << endl;
  MergeList(&L1, &L2, &L3);
  cout << "合并两个链表结束" << endl;
  ListTraverse(L3);

  return 0;
}