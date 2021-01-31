// 行逻辑的稀疏矩阵
#include "../../Status.h"
#include <iostream>
#include <string.h>
using namespace std;

#define MAXSIZE 12500 // 非零元数量的最大值
#define MAXRC 20      // 各行元素个数的最大值

typedef int ElemType;

typedef struct
{
  int i, j;
  ElemType e;
} Triple;

typedef struct
{
  Triple data[MAXSIZE + 1];
  int rpos[MAXRC + 1];
  int mu, nu, tu;
} RLSMatrix;


// 创建稀疏矩阵
Status CreateSMatrix(RLSMatrix *M, char *path);

// 销毁稀疏矩阵
Status DestorySMatrix(RLSMatrix *M);

// 复制
Status CopySMatrix(RLSMatrix M, RLSMatrix *T);

// 加法
Status AddSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q);

// 乘法
Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q);

// 转置
Status TransposeSMatrix(RLSMatrix M, RLSMatrix *T);

// 输出矩阵
void PrintSMatrix(RLSMatrix M);

static void AssignRpos(RLSMatrix *M);