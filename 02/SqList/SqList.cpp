#include "SqList.h"
/**
 * 初始化
 */
Status InitList(SqList *L)
{
  (*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
  if (!(*L).elem)
    return ERROR;
  (*L).length = 0;
  (*L).listsize = LIST_INIT_SIZE;
  return OK;
}

/**
 * 摧毁顺序表
 */
Status DestoryList(SqList *L)
{
  if (L == NULL || (*L).elem == NULL)
    return ERROR;
  free((*L).elem);
  (*L).elem = NULL;
  (*L).length = 0;
  (*L).listsize = 0;
  return OK;
}

/**
 * 清空顺序表
 */
Status ClearList(SqList *L)
{
  if (L == NULL || (*L).elem == NULL)
    return ERROR;
  (*L).length = 0;
  return OK;
}

/**
 * 判断是否为空
 */
Status ListEmpty(SqList L)
{
  return L.length == 0 ? true : false;
}

/**
 * 计数
 */
Status ListLength(SqList L)
{
  return L.length;
}

/**
 * 取值
 */
Status GetElem(SqList L, int i, ElemType *e)
{
  if (i < 1 || i > L.length)
    return ERROR;
  *e = L.elem[i - 1];
  return OK;
}

/**
 * 插入
 */
Status ListInsert(SqList *L, int i, ElemType e)
{
  if (L == NULL || (*L).elem == 0)
    return ERROR;
  if (i < 1 || i > (*L).length + 1)
    return ERROR;
  if ((*L).length >= (*L).listsize)
  {
    ElemType *newbase = (ElemType *)realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
    if (newbase == NULL)
      return ERROR;
    (*L).elem = newbase;
    (*L).listsize += LISTINCREMENT;
  }
  ElemType *p, *q;
  q = &(*L).elem[i - 1];
  for (p = &(*L).elem[(*L).length - 1]; p >= q; --p)
  {
    *(p + 1) = *p;
  }
  *q = e;
  (*L).length++;
  return OK;
}

/**
 * 删除
 */
Status ListDelete(SqList *L, int i, ElemType *e)
{
  if (L == NULL || (*L).length == 0)
    return ERROR;
  if (i < 1 || i > (*L).length)
    return ERROR;
  ElemType *p = &(*L).elem[i - 1];
  *e = *p;
  ElemType *q = (*L).elem + (*L).length - 1;
  for (++p; p <= q; ++p)
  {
    *(p - 1) = *p;
  }
  (*L).length--;
  return OK;
}

/**
 * 遍历
 */
Status ListTraverse(SqList L)
{
  for (int i = 0; i < L.length; i++)
  {
    cout << L.elem[i] << " ";
  }
  cout << endl;
}

/**
 * 合并两个顺序表
 */
void MergeList(SqList L1, SqList L2, SqList *L3)
{
  int len1 = ListLength(L1);
  int len2 = ListLength(L2);
  int i = 1, j = 1, k = 1;
  ElemType a1, a2;
  while (i <= len1 && j <= len2)
  {
    GetElem(L1, i, &a1);
    GetElem(L2, j, &a2);
    if (a1 <= a2)
    {
      ListInsert(L3, k, a1);
      i++;
    }
    else
    {
      ListInsert(L3, k, a2);
      j++;
    }
    k++;
  }

  if (i <= len1)
  {
    GetElem(L1, i++, &a1);
    ListInsert(L3, k++, a1);
  }

  if (j <= len2)
  {
    GetElem(L2, j++, &a2);
    ListInsert(L3, k++, a2);
  }
}

int main(int argc, const char *argv[])
{
  SqList L;
  ElemType e;
  printf("初始化顺序表\n");
  InitList(&L);
  ListEmpty(L) ? printf("顺序表L为空！\n") : printf("顺序表L不为空！\n");
  printf("开始插入元素\n");
  for (int i = 1; i <= 9; i++)
  {
    printf("在 L 第 %d 个位置插入 \"%d\"...\n", i, i);
    ListInsert(&L, i, i);
  }
  printf("插入元素结束\n");
  // ListEmpty(L) ? printf("顺序表L为空！\n") : printf("顺序表L不为空！\n");
  // printf("此时L内部元素为：");
  // ListTraverse(L);
  int length = ListLength(L);
  printf("此时顺序表L的长度为：%d\n", length);
  printf("开始删除元素\n");
  ListDelete(&L, 3, &e);
  printf("删除元素结束\n");
  length = ListLength(L);
  printf("此时顺序表L的长度为：%d\n", length);
  GetElem(L, 1, &e);
  cout << "此时顺序表L中第一个值为：" << e << endl;
  // printf("此时L内部元素为：");
  // ListTraverse(L);

  cout << "-------------------合并两个顺序表-------------------" << endl;
  SqList L1, L2, L3;
  // 构建L1
  cout << "----------------开始构建L1---------------" << endl;
  cout << "开始初始化顺序表" << endl;
  InitList(&L1);
  cout << "初始化顺序表结束" << endl;
  cout << "向顺序表中插入元素" << endl;
  for (int i = 1; i <= 9; i++)
  {
    printf("在 L 第 %d 个位置插入 \"%d\"...\n", i, i);
    ListInsert(&L1, i, i);
  }
  cout << "插入元素结束" << endl;
  cout << "该顺序表的长度为" << ListLength(L1) << endl;
  cout << "该顺序表内的元素依次为：";
  ListTraverse(L1);
  cout << "-----------------L1构建完成---------------" << endl;
  // 构建L2
  cout << "-----------------开始构建L2----------------" << endl;
  cout << "开始初始化顺序表" << endl;
  InitList(&L2);
  cout << "初始化顺序表结束" << endl;
  cout << "向顺序表中插入元素" << endl;
  for (int i = 1; i <= 9; i++)
  {
    printf("在 L 第 %d 个位置插入 \"%d\"...\n", i, 2 * i);
    ListInsert(&L2, i, 2 * i);
  }
  cout << "插入元素结束" << endl;
  cout << "该顺序表的长度为" << ListLength(L2) << endl;
  cout << "该顺序表内的元素依次为：";
  ListTraverse(L2);
  cout << "------------------L2构建完成----------------" << endl;
  // 合并链表
  InitList(&L3);
  MergeList(L1, L2, &L3);
  cout << "合并之后顺序表为：" << endl;
  ListTraverse(L3);
  cout << "------------------合并顺序表L1和L2结束----------------" << endl;
  return 0;
}