#include "SqStack.h"

/**
 * 初始化
 */
Status InitStack(SqStack *S)
{
  if (S == NULL)
    return ERROR;
  (*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
  if ((*S).base == NULL)
    return ERROR;
  (*S).top = (*S).base;
  (*S).stacksize = STACK_INIT_SIZE;
  return OK;
}

/**
 * 销毁栈
 */
Status DestoryStack(SqStack *S)
{
  if (S == NULL)
    return ERROR;
  free((*S).base);
  (*S).base = NULL;
  (*S).top = NULL;
  (*S).stacksize = 0;
  return OK;
}

/**
 * 置空
 */
Status ClearStack(SqStack *S)
{
  if (S == NULL || (*S).base == NULL)
    return ERROR;
  (*S).top = (*S).base;
  return OK;
}

/**
 * 判空
 */
Status StackEmpty(SqStack S)
{
  if (S.top == S.base)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * 计数
 */
Status StackLength(SqStack S)
{
  if (S.base == NULL)
    return 0;
  return (int)(S.top - S.base);
}

/**
 * 栈顶元素
 */
Status GetTop(SqStack S, SElemType *e)
{
  if (S.base == S.top)
    return ERROR;
  *e = *(S.top - 1);
  return OK;
}

/**
 * 插入
 */
Status Push(SqStack *S, SElemType e)
{
  if (S == NULL || (*S).base == NULL)
    return ERROR;
  if ((*S).top - (*S).base >= (*S).stacksize)
  {
    (*S).base = (SElemType *)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
    if ((*S).base == NULL)
      return ERROR;
    (*S).top = (*S).base + (*S).stacksize;
    (*S).stacksize += STACKINCREMENT;
  }
  *(S->top++) = e;
  return OK;
}

/**
 * 出栈
 */
Status Pop(SqStack *S, SElemType *e)
{
  if (S == NULL || (*S).base == NULL)
    return ERROR;
  if ((*S).base == (*S).top)
    return ERROR;
  *e = *(--(*S).top);
  return OK;
}

/**
 * 遍历
 */
void StackTraverse(SqStack S)
{
  SElemType *cur = S.base;
  if (S.base == NULL)
    return;
  while (cur < S.top)
  {
    cout << *cur++;
  }
  cout << endl;
}

int main()
{
  SElemType e;
  SqStack S;
  int i;
  cout << "开始初始化顺序栈" << endl;
  InitStack(&S);
  cout << "顺序栈初始化结束" << endl;

  StackEmpty(S) ? printf("顺序栈S为空\n") : printf("顺序栈S不为空\n");

  cout << "依次入栈" << endl;
  for (i = 1; i <= 6; i++)
  {
    Push(&S, i);
    printf("█ 将 \"%2d\" 压入栈 S ...\n", i);
  }
  cout << "入栈结束" << endl;

  int length = StackLength(S);
  cout << "此时栈的长度为" << length << endl;

  cout << "此时栈内元素依次为：";
  StackTraverse(S);

  cout << "弹出栈顶元素" << endl;
  Pop(&S, &e);
  cout << "弹出的栈顶元素为" << e << endl;

  cout << "此时栈内元素依次为：";
  StackTraverse(S);
  return 0;
}
