#include "HString.h"

/**
 * 初始化
 */
Status StrAssign(HString *T, const char *chars)
{
  int len = (int)strlen(chars);
  if (len == 0)
  {
    (*T).ch = NULL;
    (*T).length = 0;
    return OK;
  }
  (*T).ch = (char *)malloc(len * sizeof(char));
  if (!(*T).ch)
    return ERROR;
  for (int j = 0; j < len; j++)
  {
    (*T).ch[j] = chars[j];
  }
  (*T).length = len;
  return OK;
}

/**
 * 销毁
 */
Status DestoryString(HString *S)
{
  return OK;
}

/**
 * 清空
 */
Status ClearString(HString *S)
{
  if ((*S).ch != 0)
  {
    free((*S).ch);
    (*S).ch = NULL;
  }
  (*S).length = 0;
  return OK;
}

/**
 * 判空
 */
Status StrEmpty(HString S)
{
  return S.length == 0 ? true : false;
}

/**
 * 计数
 */
int StrLength(HString S)
{
  return S.length;
}

/**
 * 求子串
 */
Status SubString(HString *Sub, HString S, int pos, int len)
{
  if (pos < 1 || pos > S.length || len < 0 || pos + len - 1 > S.length)
    return ERROR;
  if (len == 0)
  {
    (*Sub).ch = NULL;
    (*Sub).length = 0;
    return OK;
  }
  (*Sub).ch = (char *)malloc(len * sizeof(char));
  if (!(*Sub).ch)
    return ERROR;
  for (int i = 0; i < len; i++)
  {
    (*Sub).ch[i] = S.ch[i + pos - 1];
  }
  (*Sub).length = len;
  return OK;
}

/**
 * 查找
 */
int Index(HString S, HString T, int pos)
{
  HString sub;
  if (pos < 1 || pos > S.length || StrEmpty(T))
    return 0;
  int s = S.length;
  int t = T.length;
  int i = pos;
  while (i + t - 1 <= s)
  {
    SubString(&sub, S, i, t);
    if (StrCompare(sub, T) != 0)
    {
      ++i;
    }
    else
    {
      return i;
    }
  }
  return 0;
}
/**
 * 插入
 */
Status StrInsert(HString *S, int pos, HString T)
{
  if (pos < 1 || pos > (*S).length + 1)
    return ERROR;
  if (StrEmpty(T))
    return OK;
  (*S).ch = (char *)realloc((*S).ch, ((*S).length + T.length) * sizeof(char));
  if (!(*S).ch)
    return ERROR;
  for (int i = (*S).length - 1; i >= pos; i--)
  {
    (*S).ch[i + T.length] = (*S).ch[i];
  }
  for (int i = pos - 1; i <= pos + T.length - 2; i++)
  {
    (*S).ch[i] = T.ch[i - pos + 1];
  }
  (*S).length += T.length;
  return OK;
}

/**
 * 删除
 */
Status StrDelete(HString *S, int pos, int len)
{
  if (pos < 1 || pos + len - 1 > (*S).length || len < 0)
    return ERROR;
  if (len == 0)
    return OK;
  for (int i = pos + len - 1; i <= (*S).length; i++)
  {
    (*S).ch[i - len] = (*S).ch[i];
  }
  (*S).length -= len;
  (*S).ch = (char *)realloc((*S).ch, (*S).length * sizeof(char));
  return OK;
}

/**
 * 比较
 */
int StrCompare(HString S, HString T)
{
  for (int i = 0; i < S.length && i < T.length; i++)
  {
    if (S.ch[i] != T.ch[i])
    {
      return S.ch[i] - T.ch[i];
    }
  }
  return S.length - T.length;
}

/**
 * 复制
 */
Status StrCopy(HString *T, HString S)
{
  if (StrEmpty(S))
  {
    (*T).ch = NULL;
    (*T).length = 0;
  }
  else
  {
    (*T).ch = (char *)malloc(S.length * sizeof(char));
    if (!(*T).ch)
      return ERROR;
    for (int i = 0; i < S.length; i++)
    {
      (*T).ch[i] = S.ch[i];
    }
    (*T).length = S.length;
  }
  return OK;
}

/**
 * 替换
 */
Status Replace(HString *S, HString T, HString V)
{
  if (StrEmpty(*S) || StrEmpty(T))
    return ERROR;
  int i = Index(*S, T, 1);
  while (i != 0)
  {
    StrDelete(S, i, StrLength(T));
    StrInsert(S, i, V);
    i += StrLength(V);
    i = Index(*S, T, i);
  }
  return OK;
}

/**
 * 串连接
 */
Status Concat(HString *T, HString S1, HString S2)
{
  (*T).length = S1.length + S2.length;
  (*T).ch = (char *)malloc((*T).length * sizeof(char));
  if (!(*T).ch)
    return ERROR;
  for (int i = 0; i < S1.length; i++)
  {
    (*T).ch[i] = S1.ch[i];
  }

  for (int i = 0; i < S2.length; i++)
  {
    (*T).ch[i + S1.length] = S2.ch[i];
  }
  return OK;
}

int main()
{
  return 0;
}