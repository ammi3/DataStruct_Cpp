#include "Hanoi.h"

Tower T;
int step;

void hanoi(int n, char x, char y, char z)
{
  if (n == 1)
  {
    cout << "Move disk " << n << " from " << x << " to " << z << endl;
  }
  else
  {
    hanoi(n - 1, x, z, y);
    cout << "Move disk " << n << " from " << x << " to " << z << endl;
    hanoi(n - 1, y, x, z);
  }
}

void move(char x, int n, char z)
{
  // step为全局变量，在main函数之外定义
  step++;
  printf("第%2d步：将第 %d 个圆盘从 %c 移到 %c \n", step, n, x, z);
}

int main()
{
  char x = 'x';
  char y = 'y';
  char z = 'z';
  hanoi(5, x, y, z);
  return 0;
}