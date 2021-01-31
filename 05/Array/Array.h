#include "../../Status.h"
#include <iostream>
using namespace std;

#define MAX_ARRAY_DIM 8 // 数组的最大维度

typedef int ElemType;

typedef struct
{
  ElemType *base; // 数组元素基址
  int dim;        // 数组维度
  int *bounds;    // 数组各维度基址
  int *constants; // 数组映像函数常量基址
} Array;

// 初始化
Status InitArray(Array *A, int dim, ...);

// 销毁
Status DestoryArray(Array *A);

// 取值
Status Value(Array A, ElemType *e, ...);

// 赋值
Status Assign(Array *A, ElemType e, ...);

// 求出相对位置
static Status Locate(Array A, va_list ap, int *off);

Status Print(Array A);
