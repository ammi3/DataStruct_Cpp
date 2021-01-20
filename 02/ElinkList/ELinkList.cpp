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

// 插入
Status ListInsert(ELinkList *L, int i, ElemType e)
{
  if (L == NULL || (*L).head == NULL)
    return ERROR;
  Link pre, cur;
  if (i < 1 || i > (*L).len + 1)
    return ERROR;
  if (LocatePos(*L, i - 1, &pre) == ERROR)
    return ERROR;
  if (MakeNode(&cur, i) == ERROR)
    return ERROR;
  if (InsFirst(L, pre, cur) == ERROR)
    return ERROR;
  return OK;
}

// 删除
Status ListDelete(ELinkList *L, int i, ElemType *e)
{
  if (L == NULL || (*L).head == NULL)
    return ERROR;
  if (i < 1 || i > (*L).len + 1)
    return ERROR;
  Link pre, cur;
  if (LocatePos(*L, i - 1, &pre) == ERROR)
    return ERROR;
  if (DelFirst(L, pre, &cur) == ERROR)
    return ERROR;
  *e = cur->data;
  FreeNode(&cur);
  return OK;
}

// 遍历
void ListTraverse(ELinkList L)
{
  if (L.len < 0)
    return;
  Link cur = L.head->next;
  while (cur != NULL)
  {
    cout << cur->data << " ";
    cur = cur->next;
  }
  cout << endl;
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

int main()
{
  ELinkList L;
  int i;
  ElemType e;
  cout << "开始初始化扩展的线性链表" << endl;
  InitList(&L);
  cout << "扩展的线性链表初始化结束" << endl;

  ListEmpty(L) ? printf("扩展的线性链表L为空\n") : printf("扩展的线性链表不为空\n");

  cout << "开始插入元素" << endl;
  for (i = 1; i <= 8; i++)
  {
    printf("█ 在 L 第 %d 个位置插入 \"%d\" ...\n", i, i);
    ListInsert(&L, i, i);
  }
  cout << "扩展的线性链表L插入结束" << endl;

  int length = ListLength(L);
  cout << "此时L的长度为：" << length << endl;

  cout << "此时L内的元素依次为：";
  ListTraverse(L);

  cout << "删除第三个元素" << endl;
  ListDelete(&L, 3, &e);
  cout << "删除元素结束" << endl;

  cout << "此时L内的元素依次为：";
  ListTraverse(L);

  return 0;
}