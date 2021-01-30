#include "SString.h"

/**
 * 初始化
 */
Status StrAssign(SString T, const char *chars)
{
  int len = (int)strlen(chars);
  if (len > MAXSTRLEN)
    return ERROR;
  T[0] = len;
  for (int i = 0; i <= len; i++)
  {
    T[i] = chars[i - 1];
  }
  return OK;
}

/**
 * 销毁
 */
Status DestoryString(SString S)
{
  return OK;
}

/**
 * 清空
 */
Status ClearString(SString S)
{
  S[0] = 0;
  return OK;
}

/**
 * 判空
 */
Status StrEmpty(SString S)
{
  return S[0] == 0 ? true : false;
}

/**
 * 计数
 */
int StrLength(SString S)
{
  return S[0];
}

/**
 * 求子串
 */
Status SubString(SString Sub, SString S, int pos, int len)
{
  if (pos < 1 || pos > S[0] || len < 0 || pos + len - 1 > S[0])
    return ERROR;
  for (int i = 1; i <= len; i++)
  {
    Sub[i] = S[pos + i - 1];
  }
  Sub[0] = len;
  return OK;
}

/**
 * 查找
 */
int Index_1(SString S, SString T, int pos)
{
}

/**
 * 查找
 */
int Index_2(SString S, SString T, int pos)
{
  int i = pos, j = 1;
  if (pos < 1 || pos > S[0])
    return ERROR;
  while (i <= S[0] || j <= T[0])
  {
    if (S[i] == T[j])
    {
      i++;
      j++;
    }
    else
    {
      i = i - (j - 1) + 1;
      j = 1;
    }
  }
  if (j > T[0] && T[0] > 0)
  {
    return i - T[0];
  }
  else
  {
    return 0;
  }
}

/**
 * 插入
 */
Status StrInsert(SString S, int pos, SString T)
{
  if (pos < 1 || pos > S[0] + 1 || S[0] + T[0] > MAXSTRLEN)
    return ERROR;
  if (StrEmpty(T))
    return OK;
  for (int i = S[0]; i >= pos; i--)
  {
    S[i + T[0]] = S[i];
  }
  for (int i = pos; i <= pos + T[0] - 1; i++)
  {
    S[i] = T[i - pos + 1];
  }
  S[0] += T[0];
  return OK;
}

/**
 * 删除
 */
Status StrDelete(SString S, int pos, int len)
{
  if (pos < 1 || pos > S[0] || pos + len - 1 > S[0] || len < 0)
    return ERROR;
  if (len == 0)
    return OK;
  for (int i = pos + len; i <= S[0]; i++)
  {
    S[i - len] = S[i];
  }
  S[0] -= len;
  return OK;
}

/**
 * 比较
 */
int StrCompare(SString S, SString T)
{
  int i = 1;
  while (i <= S[0] && i <= T[0])
  {
    if (S[i] != T[i])
    {
      return S[i] - T[i];
    }
    i++;
  }
  return S[0] - T[0];
}

/**
 * 复制
 */
Status StrCopy(SString T, SString S)
{
  for (int i = 0; i <= S[0]; i++)
  {
    T[i] = S[i];
  }
  return OK;
}

/**
 * 替换
 */
Status Replace(SString S, SString T, SString V)
{
  if (StrEmpty(S) || StrEmpty(T))
    return ERROR;
  int i = Index_2(S, T, 1);
  while (i != 0 && S[0] - T[0] + V[0] <= MAXSTRLEN)
  {
    StrDelete(S, i, StrLength(T));
    StrInsert(S, i, V);
    i += StrLength(V);
    i = Index_2(S, T, i);
  }
  if (i == 0)
  {
    return OK;
  }
  else
  {
    return ERROR;
  }
}

/**
 * 连接
 */
Status Concat(SString T, SString S1, SString S2)
{
  int uncut;
  if (S1[0] + S2[0] <= MAXSTRLEN)
  {
    for (int i = 1; i <= S1[0]; i++)
    {
      T[i] = S1[i];
    }

    for (int i = S1[0] + 1; i <= S1[0] + S2[0]; i++)
    {
      T[i] = S2[i - S1[0]];
    }
    T[0] = S1[0] + S2[0];
    uncut = true;
  }
  else if (S1[0] <= MAXSTRLEN)
  {
    for (int i = 1; i <= S1[0]; i++)
    {
      T[i] = S1[i];
    }

    for (int i = S1[0] + 1; i <= MAXSTRLEN; i++)
    {
      T[i] = S2[i - S1[0]];
    }
    T[0] = MAXSTRLEN;
    uncut = false;
  }
  else
  {
    for (int i = 0; i <= MAXSTRLEN; i++)
    {
      T[i] = S1[i];
    }

    uncut = FALSE;
  }
  return uncut;
}

int main()
{
  char *chars = "01234567899876543210";
  SString S, T, Sub, V;
  cout << "初始化，为顺序串S赋值" << endl;
  StrAssign(S, chars);
  cout << "初始化结束" << endl;

  StrEmpty(S) ? printf("此时S为空！\n") : printf("此时S不为空！\n");

  int length = StrLength(S);
  cout << "此时S的长度为：" << length << endl;

  cout << "将S复制到T" << endl;
  StrCopy(T, S);
  cout << "复制完成" << endl;

  int flag;
  flag = StrCompare(S, T);
  flag == 0 ? printf("S==T\n") : printf("S!=T\n");

  cout << "将***插入到S的第11个位置处" << endl;
  StrAssign(T, "***");
  StrInsert(S, 11, T);
  cout << "S：" << S << endl;

  cout << "获取***在S中第一次出现的位置" << endl;
  int i = Index_2(S, T, 1);
  cout << "第一次出现的位置是：" << i << endl;

  return 0;
}