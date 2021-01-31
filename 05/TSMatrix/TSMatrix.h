#include "../../Status.h"
#include <iostream>
#include <string.h>
using namespace std;

#define MAXSIZE 12500

typedef int ElemType;

typedef struct
{
  int i, j; // 矩阵中非零元的下标
  ElemType e;
} Triple;

typedef struct
{
  Triple data[MAXSIZE + 1];
  int mu, nu, tu; // 矩阵的行数，列数和非零元个数
} TSMatrix;

// 创建稀疏矩阵
Status CreateSMatrix(TSMatrix *M);

// 销毁稀疏矩阵
Status DestorySMatrix(TSMatrix *M);

// 复制
Status CopySMatrix(TSMatrix M, TSMatrix *T);

// 加法
Status AddSMatrix(TSMatrix M, TSMatrix T, TSMatrix *Q);

// 乘法
Status MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q);

// 转置
Status TransposeSMatrix(TSMatrix M, TSMatrix *T);

// 快速转置
Status FastTransposeSMatrix(TSMatrix M, TSMatrix *T);

// 输出矩阵
void PrintSMatrix(TSMatrix M);