#include "SLinkList.h"

// space：备用空间
// S：头结点的索引

/**
 * 初始化空间
 */
void InitSpace(SLinkList space)
{
  for (int i = 0; i < MAXSIZE - 1; i++)
  {
    space[i].cur = i + 1;
  }
  space[MAXSIZE - 1].cur = 0;
}

/**
 * 申请空间
 */
int Malloc(SLinkList space)
{
  int i = space[0].cur;
  if (i != 0)
  {
    space[0].cur = space[i].cur;
  }
  return i;
}

/**
 * 回收空间
 */
void Free(SLinkList space, int k)
{
  space[k].cur = space[0].cur;
  space[0].cur = k;
}

/**
 * 初始化静态链表
 */
Status InitList(SLinkList space, int *S)
{
  // 初始化备用空间
  InitSpace(space);
  // 申请头结点空间
  int index = Malloc(space);
  if (index == 0)
    return ERROR;
  space[index].cur = 0;
  *S = index;
  return OK;
}

/**
 * 销毁
 */
Status DestoryList(SLinkList space, int *S)
{
  int cur;
  if (S == NULL || *S == 0)
    return ERROR;
  while (*S != 0)
  {
    cur = space[*S].cur; // 保存当前节点下一个结点的索引
    Free(space, *S);     // 回收当前结点的空间
    *S = cur;            // 索引到下一个结点
  }
  return OK;
}

/**
 * 清空链表
 */
Status ClearList(SLinkList space, int S)
{
  int cur, p;
  if (S == 0)
    return ERROR;
  p = space[S].cur;
  while (p != 0)
  {
    cur = space[p].cur;
    Free(space, p);
    p = cur;
  }
  space[S].cur = 0;
  return OK;
}

/**
 * 判断是否为空
 */
Status ListEmpty(SLinkList space, int S)
{
  if (S != 0 && space[S].cur == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// 计数
Status ListLength(SLinkList space, int S)
{
  int len = 0;

  if (S == 0 || space[S].cur == 0)
    return 0;
  S = space[S].cur;
  while (S != 0)
  {
    len++;
    S = space[S].cur;
  }
  return len;
}

/**
 * 取值
 */
Status GetElem(SLinkList space, int S, int i, ElemType *e)
{

  if (S == 0 || space[S].cur == 0)
    return ERROR;

  int k = 0;
  S = space[S].cur;
  while (S != 0 && k < i - 1)
  {
    k++;
    S = space[S].cur;
  }
  *e = space[S].data;
  return OK;
}

/**
 * 插入
 */
Status ListInsert(SLinkList space, int S, int i, ElemType e)
{
  if (S == 0)
    return ERROR;
  int k = 0;
  int pre = S;
  while (pre != 0 && k < i - 1)
  {
    pre = space[pre].cur;
    ++k;
  }
  if (pre == 0 || k > i - 1)
    return ERROR;
  int cur = Malloc(space);
  space[cur].data = e;
  space[cur].cur = space[pre].cur;
  space[pre].cur = cur;
  return OK;
}

/**
 * 删除
 */
Status ListDelete(SLinkList space, int S, int i, ElemType *e)
{
  if (S == 0 || space[S].cur == 0)
    return ERROR;
  int k = 0;
  int pre = S;
  while (space[pre].cur != 0 && k < i - 1)
  {
    pre = space[pre].cur;
    ++k;
  }
  if (space[pre].cur == 0 || k > i - 1)
    return ERROR;
  int cur = space[pre].cur;
  space[pre].cur = space[cur].cur;
  *e = space[cur].data;
  Free(space, cur);
  return OK;
}

/**
 * 遍历
 */
Status ListTraverse(SLinkList space, int S)
{
  if (S == 0 || space[S].cur == 0)
    return ERROR;
  int cur = space[S].cur;
  while (cur != 0)
  {
    cout << space[cur].data << " ";
    cur = space[cur].cur;
  }
  return OK;
}

// 表示 (A-B)∪(B-A)
void difference(SLinkList space, int *S)
{
  int m, n, i, p, k;
  int R;
  int b;
  InitSpace(space);
  *S = Malloc(space);
  R = *S;

  cout << "请输入集合A的元素个数：" << endl;
  cin >> m;
  cout << "请输入集合B的元素个数" << endl;
  cin >> n;
  // 录入集合A
  for (int j = 1; j <= m; ++j)
  {
    i = Malloc(space);
    cin >> space[i].data;
    space[R].cur = i;
    R = i;
  }
  space[R].cur = 0;

  // 录入集合B
  for (int j = 1; j <= n; ++j)
  {
    cin >> b;
    p = *S;
    k = space[*S].cur;
    while (k != space[R].cur && space[k].data != b)
    {
      p = k;
      k = space[k].cur;
    }

    if (k == space[R].cur)
    {
      i = Malloc(space);
      space[i].data = b;
      space[i].cur = space[R].cur;
      space[R].cur = i;
    }
    else
    {
      space[p].cur = space[k].cur;
      Free(space, k);
      if (R == k)
        R = p;
    }
  }
}

int main()
{
  SLinkList space;
  int S;
  ElemType e;

  cout << "开始初始化静态链表" << endl;
  InitList(space, &S);
  cout << "静态链表初始化结束" << endl;

  ListEmpty(space, S) ? printf("静态链表为空") : printf("静态链表不为空");

  cout << "开始向静态链表内插入元素" << endl;
  for (int i = 1; i <= 8; i++)
  {
    printf("█ 在 S 第 %d 个位置插入 \"%d\" ...\n", i, i);
    ListInsert(space, S, i, i);
  }
  cout << "静态链表插入结束" << endl;

  cout << "此时静态链表S内的元素为：";
  ListTraverse(space, S);
  cout << endl;

  int length = ListLength(space, S);
  cout << "此时静态链表S的长度为：" << length << endl;

  GetElem(space, S, 5, &e);
  cout << "此时静态链表S中第5个元素为：" << e << endl;

  cout << "删除静态链表S中第5个元素" << endl;
  ListDelete(space, S, 5, &e);
  cout << "删除结束" << endl;

  cout << "删除之后静态链表元素依次为：";
  ListTraverse(space, S);
  return 0;
}