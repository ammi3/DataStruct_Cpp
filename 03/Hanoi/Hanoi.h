#include "../../Status.h"
#include <iostream>
using namespace std;

#define N 5
typedef struct
{
  int **plates;
  int high[3];
} Tower;

/*
 * 汉诺塔求解：以y塔为辅助，将x塔上前n个圆盘移动到z塔
 */
void hanoi(int n, char x, char y, char z);

/*
 * 移动汉诺塔圆盘：将第n个圆盘从x塔移到z塔。
 */
void move(char x, int n, char z);