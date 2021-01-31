#include "TSMatrix.h"

/**
 * 创建稀疏矩阵
 */
Status CreateSMatrix(TSMatrix *M)
{
  cout << "请输入行数：" << endl;
  cin >> (*M).mu;
  cout << "请输入列数：" << endl;
  cin >> (*M).nu;
  cout << "请输入非零元的个数：" << endl;
  cin >> (*M).tu;

  for (int k = 1; k <= (*M).tu; k++)
  {
    cout << "第" << k << "组" << endl;
    scanf("%d%d%d", &((*M).data[k].i), &((*M).data[k].j), &((*M).data[k].e));
  }

  return OK;
}

/**
 * 销毁
 */
Status DestorySMatrix(TSMatrix *M)
{
  if (M == NULL)
    return ERROR;
  (*M).mu = 0;
  (*M).nu = 0;
  (*M).tu = 0;
  return OK;
}

/**
 * 矩阵复制
 */
Status CopySMatrix(TSMatrix M, TSMatrix *T)
{
  (*T) = M;
  return OK;
}

/**
 * 矩阵相加
 */
Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q)
{
  if (M.mu != N.mu || M.nu != N.nu)
    return ERROR;

  (*Q).mu = M.mu;
  (*Q).nu = M.nu;
  (*Q).tu = 0;

  int m = 1, n = 1, k = 1;

  while (m <= M.tu && n <= N.tu)
  {
    if (M.data[m].i < N.data[n].i)
    {
      (*Q).data[k] = M.data[m];
      m++;
    }
    else if (M.data[m].i > N.data[n].i)
    {
      (*Q).data[k] = N.data[n];
      n++;
    }
    else
    {
      if (M.data[m].j < N.data[n].j)
      {
        (*Q).data[k] = N.data[n];
        n++;
      }
      else if (M.data[m].j > N.data[n].j)
      {
        (*Q).data[k] = N.data[n];
        n++;
      }
      else
      {
        if (M.data[m].e + N.data[n].e == 0)
        {
          m++;
          n++;
          continue;
        }
        else
        {
          (*Q).data[k].i = M.data[m].i;
          (*Q).data[k].j = M.data[m].j;
          (*Q).data[k].e = M.data[m].e + N.data[n].e;
          m++;
          n++;
        }
      }
    }

    k++;
    (*Q).tu++;
  }

  while (m <= M.tu)
  {
    (*Q).data[k] = M.data[m];
    m++;
    k++;
    (*Q).tu++;
  }

  while (n <= N.tu)
  {
    (*Q).data[k] = N.data[n];
    n++;
    k++;
    (*Q).tu++;
  }

  return OK;
}

/**
 * 乘法
 */
Status MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q)
{
  ElemType c, c1, c2;
  if (M.mu != N.mu)
    return ERROR;

  // 初始化Q
  (*Q).mu = M.mu;
  (*Q).nu = N.nu;
  (*Q).tu = 0;

  if (M.tu * N.tu == 0)
    return OK;

  for (int i = 1; i <= M.mu; i++)
  {
    for (int j = 1; j <= N.nu; j++)
    {
      c = 0;
      for (int k = 1; k <= M.nu; k++)
      {
        // 记录M[i][k]的值
        c1 = 0;
        for (int m = 1; m <= M.tu; m++)
        {
          if (M.data[m].i == i && M.data[m].j == k)
          {
            c1 = M.data[m].e;
            break;
          }
        }

        c2 = 0;
        for (int n = 1; n <= N.tu; n++)
        {
          if (N.data[n].i == k && N.data[n].j == j)
          {
            c2 = N.data[n].e;
            break;
          }
        }

        if (c1 && c2)
        {
          c1 += c1 * c2;
        }
      }

      if (c != 0)
      {
        (*Q).tu++;
        (*Q).data[(*Q).tu].i = i;
        (*Q).data[(*Q).tu].j = j;
        (*Q).data[(*Q).tu].e = c;
      }
    }
  }

  return OK;
}

/**
 * 转置矩阵
 */
Status TransposeSMatrix(TSMatrix M, TSMatrix *T)
{
  int p, q, col;
  (*T).mu = M.nu;
  (*T).nu = M.mu;
  (*T).tu = M.tu;

  if ((*T).tu != 0)
  {
    q = 1;
    for (col = 1; col <= M.nu; ++col)
    {
      for (p = 1; p <= M.tu; ++p)
      {
        if (M.data[p].j == col)
        {
          (*T).data[q].i = M.data[p].j;
          (*T).data[q].j = M.data[p].i;
          (*T).data[q].e = M.data[p].e;
          ++q;
        }
      }
    }
  }

  return OK;
}

/**
 * 快速转置
 */
Status FastTransposeSMatrix(TSMatrix M, TSMatrix *T)
{
  int col, t, p, q;
  int *num;  // num[col]表示M第col列中非零元的个数
  int *copt; // cpot[col]表示M第col列第一个非零元在转置后矩阵中的位置

  (*T).mu = M.nu;
  (*T).nu = M.mu;
  (*T).tu = M.tu;

  if ((*T).tu == 0)
    return ERROR;

  num = (int *)malloc((M.tu + 1) * sizeof(int));
  copt = (int *)malloc((M.nu + 1) * sizeof(int));

  for (col = 1; col <= M.nu; ++col)
  {
    num[col] = 0;
  }

  for (t = 1; t <= M.tu; ++t)
  {
    num[M.data[t].j]++;
  }

  copt[1] = 1;

  for (col = 2; col <= M.nu; ++col)
  {
    copt[col] = copt[col - 1] + num[col - 1];
  }

  for(p = 1; p <= M.tu; ++p) {
    col = M.data[p].j; // 计算当前非零元所处的列
    q = copt[col]; // 计算当前非零元在转置矩阵中的位置
    (*T).data[q].i = M.data[p].j;
    (*T).data[q].j = M.data[p].i;
    (*T).data[q].e = M.data[p].e;
    ++copt[col];
  }

  return OK;
}

/**
 * 输出矩阵
 */
void PrintSMatrix(TSMatrix M)
{
  int r, c;
  int k = 1;

  for (r = 1; r <= M.mu; r++)
  {
    for (c = 1; c <= M.nu; c++)
    {
      if (r == M.data[k].i && c == M.data[k].j)
      {
        printf("%3d ", M.data[k].e);
        k++;
      }
      else
      {
        printf("%3d ", 0);
      }
    }
    printf("\n");
  }
}

int main()
{
  TSMatrix M, N;
  cout << "开始创建两个稀疏矩阵" << endl;
  CreateSMatrix(&M);
  CreateSMatrix(&N);
  cout << "创建稀疏矩阵结束" << endl;

  cout << "M=" << endl;
  PrintSMatrix(M);

  cout << "N=" << endl;
  PrintSMatrix(N);

  TSMatrix Temp;
  cout << "复制M到Temp" << endl;
  CopySMatrix(M, &Temp);
  cout << "复制结束" << endl;

  cout << "Temp=" << endl;
  PrintSMatrix(Temp);

  TSMatrix Q1;
  cout << "对M和N进行加法运算" << endl;
  AddSMatrix(M, N, &Q1);

  cout << "Q1=" << endl;
  PrintSMatrix(Q1);

  TSMatrix Q2;
  cout << "对M和N进行乘法运算" << endl;
  MultSMatrix(M, N, &Q2);

  cout << "Q2=" << endl;
  PrintSMatrix(Q2);
  return 0;
}