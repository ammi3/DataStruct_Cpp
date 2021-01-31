#include "Array.h"

// 初始化
Status InitArray(Array *A, int dim, ...)
{
  int elemtotal; // 统计数组中总元素的个数
  va_list ap;    // ap存放可变参数信息，指示各维度的大小
  int i;

  if (A == NULL)
    return ERROR;

  if (dim < 1 || dim > MAX_ARRAY_DIM)
    return ERROR;

  (*A).dim = dim; // 初始化数组维度

  // 初始化数组维度信息表
  (*A).bounds = (int *)malloc(dim * sizeof(int));
  if ((*A).bounds == NULL)
    return ERROR;
  elemtotal = 1;

  va_start(ap, dim); //使ap指向第一个可变参数

  for (int i = 0; i < dim; i++)
  {
    (*A).bounds[i] = va_arg(ap, int);
    if ((*A).bounds[i] <= 0)
      return ERROR;
    elemtotal *= A->bounds[i];
  }

  // 置空
  va_end(ap);

  // 初始化数组空间，存放元素
  (*A).base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
  if ((*A).base == NULL)
    return ERROR;

  // 初始化数组映像函数常量信息表
  (*A).constants = (int *)malloc(dim * sizeof(int));
  if ((*A).constants == NULL)
    return ERROR;

  (*A).constants[dim - 1] = 1;
  for (i = dim - 2; i >= 0; i--)
  {
    (*A).constants[i] = (*A).bounds[i + 1] * (*A).constants[i + 1];
  }
  return OK;
}

/**
 * 销毁 
 */
Status DestoryArray(Array *A)
{

  if (A == NULL || (*A).base == NULL || (*A).bounds == NULL || (*A).constants == NULL)
    return ERROR;

  free((*A).base);
  (*A).base = NULL;

  free((*A).bounds);
  (*A).bounds = NULL;

  free((*A).constants);
  (*A).constants = NULL;

  (*A).dim = 0;

  return OK;
}

Status Value(Array A, ElemType *e, ...)
{
  va_list ap;
  Status result;
  int off;

  va_start(ap, e);

  // 计算从起点元素到目标元素需要跨越的元素数量
  result = Locate(A, ap, &off);

  va_end(ap);

  if (result == OVERFLOW)
    return result;

  *e = *(A.base + off);

  return OK;
}

Status Assign(Array *A, ElemType e, ...)
{
  va_list ap;
  Status result;
  int off;

  va_start(ap, e);

  // 计算从起点元素到目标元素需要跨越的元素数量
  result = Locate(*A, ap, &off);

  va_end(ap);

  if (result == OVERFLOW)
    return result;

  *(A->base + off) = e;

  return OK;
}

static Status Locate(Array A, va_list ap, int *off)
{
  int i, ind;

  *off = 0;

  for (int i = 0; i < A.dim; i++)
  {
    ind = va_arg(ap, int);
    if (ind < 0 || ind >= A.bounds[i])
      return OVERFLOW;
    *off += A.constants[i] * ind;
  }

  return OK;
}

Status Print(Array A)
{
}

int mian()
{
  Array A;
  ElemType e = 0;
  ElemType val;

  cout << "开始初始化数组" << endl;
  InitArray(&A, 3, 2, 3, 4);
  cout << "初始化数组结束" << endl;

  for (int i = 0; i < A.bounds[0]; i++)
  {
    for (int j = 0; j < A.bounds[1]; j++)
    {
      for (int k = 0; k < A.bounds[2]; k++)
      {
        printf("█ 赋值：A[%d][%d][%d] = %d\n", i, j, k, ++e);
        Assign(&A, e, i, j, k);
      }
    }
  }
  cout << "赋值结束！" << endl;

  cout << "获取数组中下标为(1,1,1)的元素的值" << endl;
  Value(A, &val, 1, 1, 1);
  cout << "A[1][1][1]=" << val << endl;

  cout << "数组A销毁前" << endl;
  A.dim == 0 ? printf("A为空！\n") : printf("A不为空！\n");

  cout << "数组A销毁后" << endl;
  A.dim == 0 ? printf("A为空！\n") : printf("A不为空！\n");
  return 0;
}