#include "DuLinkList.h"

/**
 * 初始化
 */
Status InitList(DuLinkList *L)
{
  *L = (DuLinkList)malloc(sizeof(DuLNode));
  if (*L == NULL)
    return ERROR;
  (*L)->next = (*L)->prior = *L;
  return OK;
}

// 销毁
Status DestoryList(DuLinkList *L)
{
  if (L == NULL || *L == NULL)
    return ERROR;
  ClearList(*L);
  free(*L);
  *L = NULL;
  return OK;
}

// 置空
Status ClearList(DuLinkList L)
{
  if (L == NULL)
    return ERROR;
  DuLinkList pre, cur;
  pre = L->next;
  while (pre != L)
  {
    cur = pre->next;
    free(pre);
    pre = cur;
  }
  L->next = L->prior = L;
  return OK;
}

// 判空
Status ListEmpty(DuLinkList L)
{
  if (L != NULL && L->next == L && L->prior == L)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// 计数
int ListLength(DuLinkList L)
{
  int len = 0;
  if (L == NULL || L->next == L || L->prior == L)
    return 0;
  DuLinkList cur = L->next;
  while (cur != L)
  {
    len++;
    cur = cur->next;
  }
  return len;
}

// 查找
Status GetElem(DuLinkList L, int i, ElemType *e)
{
  if (L == NULL || L->next == L || L->prior == L)
    return ERROR;
  DuLinkList pre = L;
  int j = 0;
  while (pre != L && j < i - 1)
  {
    pre = pre->next;
    ++j;
  }
  if (pre == L || j < i - 1)
    return ERROR;
  *e = pre->next->data;
  return OK;
}

// 插入
Status ListInsert(DuLinkList L, int i, ElemType e)
{
  if (L == NULL)
    return ERROR;
  DuLinkList next;
  // 查找第i个结点位置（引用）
  if ((next = GetElemP(L, i)) == NULL)
  {
    return ERROR;
  }
  DuLinkList cur = (DuLinkList)malloc(sizeof(DuLNode));
  if (cur == NULL)
    return ERROR;
  cur->data = e;
  cur->prior = next->prior;
  next->prior->next = cur;
  cur->next = next;
  next->prior = cur;
  return OK;
}

// 删除
Status ListDelete(DuLinkList L, int i, ElemType *e)
{
  if (L == NULL || L->next == L || L->prior == L)
    return ERROR;
  DuLinkList cur;
  // 查找第i个结点位置（引用）
  if ((cur = GetElemP(L, i)) == NULL)
    return ERROR;
  if (cur == L)
    return ERROR;
  *e = cur->data;
  cur->prior->next = cur->next;
  cur->next->prior = cur->prior;
  free(cur);
  return OK;
}

// 遍历
void ListTraverse(DuLinkList L)
{
  if (L == NULL || L->next == L || L->prior == L)
    return;
  DuLinkList cur = L->next;
  while (cur != L)
  {
    cout << cur->data << " ";
    cur = cur->next;
  }
  cout << endl;
}

static DuLinkList GetElemP(DuLinkList L, int i)
{
  if (L == NULL)
  {
    return NULL;
  }

  // 位置不合规
  if (i < 1)
  {
    return NULL;
  }

  int count = 0;
  DuLinkList cur = L;
  while (cur->next != L && count < i)
  {
    cur = cur->next;
    ++count;
  }
  // 恰好找到第i个元素
  if (count == i)
  {
    return cur;
  }

  // 至此，说明p->next==L，此时需要判断i是否过大
  if (count + 1 < i)
  {
    return NULL;
  }

  // 至此，说明需要在len+1的位置上插入元素
  return L;
}

int main()
{
  DuLinkList L;
  ElemType e;
  cout << "开始初始化循环链表" << endl;
  InitList(&L);
  cout << "初始化循环链表结束" << endl;

  ListEmpty(L) ? printf("循环链表为空") : printf("循环链表不为空");

  cout << "开始向循环链表插入元素" << endl;
  for (int i = 1; i <= 8; i++)
  {
    printf("█ 在 L 第 %d 个位置插入 \"%d\" ...\n", i, i);
    ListInsert(L, i, i);
  }
  cout << "插入元素结束" << endl;

  cout << "此时循环链表L内的元素依次为：";
  ListTraverse(L);

  int len = ListLength(L);
  cout << "此时循环链表L的长度为：" << len << endl;

  cout << "删除循环链表第2个元素";
  ListDelete(L, 2, &e);

  cout << "此时循环链表L内的元素依次为：";
  ListTraverse(L);
  return 0;
}