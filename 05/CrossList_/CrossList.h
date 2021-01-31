#include "../../Status.h"
#include <iostream>
#include <string.h>
using namespace std;

// 十字链表元素类型
typedef int ElemType;

// 非零元类型定义
typedef struct OLNode
{
  int i, j; // 非零元的行下标与列下标
  ElemType e;
  struct OLNode *right; // 该非零元所在行表的后继链域
  struct OLNode *down;  // 该非零元所在列表的后继链域
} OLNode, *OLink;

typedef struct
{
  OLink *rhead; // 行链表头指针
  OLink *chead; // 列链表头指针
  int mu, nu, tu;
} CrossList;

Status CreateSMatrix(CrossList *M, char *path);

/*
 * 销毁稀疏矩阵
 */
Status DestroySMatrix(CrossList *M);

/*
 * 矩阵复制
 *
 * 创建一个新矩阵T，该矩阵包含了从矩阵M中包含的数据。
 */
Status CopySMatrix(CrossList M, CrossList *T);

/*
 * 矩阵加法
 *
 * Q = M + N。
 */
Status AddSMatrix(CrossList M, CrossList N, CrossList *Q);

/*
 * 矩阵乘法
 *
 * Q = M * N。
 */
Status MultSMatrix(CrossList M, CrossList N, CrossList *Q);

/*
 * 矩阵转置
 */
Status TransposeSMatrix(CrossList M, CrossList *T);

/*
 * 输出矩阵
 */
void PrintSMatrix(CrossList M);