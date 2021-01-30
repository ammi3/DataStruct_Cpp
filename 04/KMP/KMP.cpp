#include "KMP.h"

int Index_KMP(SString S, SString T, int pos, int next[])
{
  int i = pos;
  int j = 1;
  if (pos < 1)
    return 0;

  while (i <= S[0] && j <= T[0])
  {
    if (j == 0 || S[i] == T[j])
    {
      i++;
      j++;
    }
    else
    {
      j = next[j];
    }

    if (j > T[0])
    {
      return i - T[0];
    }
    else
    {
      return 0;
    }
  }
}

void get_next(SString T, int next[])
{
  int i = 1;
  int j = 0;

  next[1] = 0;
  while (i < T[0])
  {
    if (j == 0 || T[i] == T[j])
    {
      i++;
      j++;
      next[i] = j;
    }
    else
    {
      j = next[j];
    }
  }
}

void get_nextVal(SString T, int nextVal[])
{
  int i = 1;
  int j = 0;
  nextVal[1] = 0;
  while (i < T[0])
  {
    if (j == 0 || T[i] == T[j])
    {
      i++;
      j++;

      if (T[i] != T[j])
      {
        nextVal[i] = j;
      }
      else
      {
        nextVal[i] = nextVal[j];
      }
    }
    else
    {
      j = nextVal[j];
    }
  }
}

int main()
{
  char *s = "abaaabcaabaabcacabaabcaabaabcac";
  char *t = "abaabcac";
  SString S, T;
  int *next;
  int *nextVal;
  int pos;
  int i, j;

  StrAssign(S, s);
  cout << "S：" << S << endl;

  StrAssign(T, t);
  cout << "T：" << T << endl;

  next = (int *)malloc((T[0] + 1) * sizeof(int));
  nextVal = (int *)malloc((T[0] + 1) * sizeof(int));

  get_next(T, next);
  get_nextVal(T, nextVal);

  pos = 1;
  i = Index_KMP(S, T, pos, next);
  j = Index_KMP(S, T, pos, nextVal);

  cout << "从第" << pos << "个字符起，T在S中第一次匹配成功的位置是：" << i << endl;
  cout << "从第" << pos << "个字符起，T在S中第一次匹配成功的位置是：" << j << endl;
  return 0;
}