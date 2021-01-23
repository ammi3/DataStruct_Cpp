#include "Conversion.h"

// void conversion(SqStack *S, SElemType e)
// {
//   int N = 1348;
//   int tmp = N;
//   // scanf("%d", N);
//   while (N)
//   {
//     Push(S, N % 8);
//     N = N / 8;
//   }

//   cout << "十进制数" << tmp << "转换为8进制为：";
//   while (StackEmpty(*S) == false)
//   {
//     Pop(S, &e);
//     cout << e;
//   }

//   cout << endl;
// }

int main()
{
  SqStack S;
  SElemType e;
  int N = 1348;
  int tmp = N;

  InitStack(&S);
  
  // scanf("%d", N);
  while (N)
  {
    Push(&S, N % 8);
    N = N / 8;
  }

  cout << "十进制数" << tmp << "转换为8进制为：";
  while (StackEmpty(S) == false)
  {
    Pop(&S, &e);
    cout << e;
  }

  cout << endl;
  return 0;
}