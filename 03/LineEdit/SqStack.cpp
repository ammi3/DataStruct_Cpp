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
