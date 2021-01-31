#include "RLSMatrix.h"

/**
 * 创建
 */
Status CreateSMatrix(RLSMatrix *M, char *path)
{
  FILE *fp;
  int readFromConsole;

  readFromConsole = path == NULL || strcmp(path, "") == 0;

  if (readFromConsole)
  {
    cout << "请输入行数" << endl;
    cin >> (*M).mu;
    cout << "请输入列数" << endl;
    cin >> (*M).nu;
    cout << "请输入非零元的个数" << endl;
    cin >> (*M).tu;

    for (int k = 1; k <= (*M).tu; k++)
    {
      cout << "第" << k << "组" << endl;
      scanf("%d%d%d", &((*M).data[k].i), &((*M).data[k].j), &((*M).data[k].e));
    }
  }
  else
  {
    fp = fopen(path, "r");
    ReadData(fp, "%d%d%d", &((*M).mu), &((*M).nu), &((*M).tu));

    for (int k = 1; k <= (*M).tu; k++)
    {
      ReadData(fp, "%d%d%d", &((*M).data[k].i), &((*M).data[k].j), &((*M).data[k].e));
    }

    fclose(fp);
  }
  AssignRpos(M);
}

/**
 * 销毁
 */
Status DestorySMatrix(RLSMatrix *M)
{
  if (M == NULL)
    return ERROR;

  M->mu = 0;
  M->nu = 0;
  M->tu = 0;

  for (int i = 0; i <= MAXRC; ++i)
  {
    M->rpos[i] = 0;
  }
  return OK;
}

/**
 * 复制 
 */
Status CopySMatrix(RLSMatrix M, RLSMatrix *T)
{
  (*T) = M; // 结构体之间可以直接复制，即使内部包含数组也可以

  return OK;
}

/**
 * 行逻辑连接的顺序表加法
 */
Status AddSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q)
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
        (*Q).data[k] = M.data[m];
        m++;
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

  // 遍历M中剩余的三元组
  while (m <= M.tu)
  {
    (*Q).data[k] = M.data[m];
    m++;
    k++;
    (*Q).tu++;
  }

  // 遍历N中剩余的三元组
  while (n <= N.tu)
  {
    (*Q).data[k] = N.data[n];
    n++;
    k++;
    (*Q).tu++;
  }

  // 为rpos数组赋值
  AssignRpos(Q);
  return OK;
}

/**
 * 矩阵乘法
 */
Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q)
{
  int arow, p, tp;
  int brow, q, tq;
  int ccol;
  int *ctemp; // Q中各行元素累加器
  int i;

  if (M.mu != N.nu)
    return ERROR;

  (*Q).mu = M.mu;
  (*Q).nu = N.nu;
  (*Q).tu = 0;

  if (M.tu * M.tu == 0)
    return OK;

  ctemp = (int *)malloc((N.nu + 1) * sizeof(int));

  // 处理M中的每一行
  for (arow = 1; arow <= M.mu; ++arow)
  {
    // 初始化Q中行元素计数器
    for (i = 0; i <= N.nu; ++i)
    {
      ctemp[i] = 0;
    }

    // tp指向M当前行的下一行第一个非零元位置
    if (arow < M.mu)
    {
      tp = M.rpos[arow + 1];
    }
    else
    {
      tp = M.tu + 1;
    }

    // 遍历M中arow行的所有非零元
    for (p = M.rpos[arow]; p < tp; ++p)
    {
      // 获取该非零元在N中的行号
      brow = M.data[p].j;

      if (brow < N.mu)
      {
        tq = N.rpos[brow + 1];
      }
      else
      {
        tq = N.tu + 1;
      }
    }

    // 遍历N中brow行的所有非零元
    for (q = N.rpos[brow]; q < tq; ++q)
    {
      ccol = N.data[q].j;
      ctemp[ccol] += M.data[p].e * N.data[q].e;
    }
  }

  for (ccol = 1; ccol <= (*Q).nu; ++ccol)
  {
    if (ctemp[ccol])
    {
      ++(*Q).tu;

      if ((*Q).tu > MAXSIZE)
        return ERROR;

      (*Q).data[(*Q).tu].i = arow;
      (*Q).data[(*Q).tu].j = ccol;
      (*Q).data[(*Q).tu].e = ctemp[ccol];
    }
  }

  AssignRpos(Q);
  return OK;
}

/**
 * 矩阵转置
 */
Status TransposeSMatrix(RLSMatrix M, RLSMatrix *T)
{
  int p, q, col;
  (*T).mu = M.nu;
  (*T).nu = M.mu;
  (*T).tu = M.tu;

  if ((*T).tu)
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

  AssignRpos(T);
  return OK;
}

// 为rpos数组赋值
static void AssignRpos(RLSMatrix *M)
{
  int k, m;

  // 初始化数组rpos
  for (k = 0; k <= MAXRC; ++k)
  {
    (*M).rpos[k] = 0;
  }

  for (k = 1; k <= (*M).tu; k++)
  {
    m = (*M).data[k].i; // 当前三元组元素在矩阵中的行位置

    // 记录每行第一个非零元的在三元组表中的位置
    if ((*M).rpos[m] == 0)
    {
      (*M).rpos[m] = k; // 只会在当前行有非零元的情况下记录
    }
  }

  // 处理那些没有非零元的行
  for (k = (*M).mu; k >= 1; k--)
  {
    // 如果当前行没有非零元，则此处会直接取用下一行的参数
    if ((*M).rpos[k] == 0)
    {
      // 如果是最后一行无非零元，因为已经不存在下一行了，所以需特殊处理
      if (k == (*M).mu)
      {
        (*M).rpos[k] = (*M).tu + 1;
      }
      else
      {
        (*M).rpos[k] = (*M).rpos[k + 1];
      }
    }
  }
}

int main()
{
  RLSMatrix M, N;

  cout << "开始创建两个稀疏矩阵" << endl;
  CreateSMatrix(&M, "TestData_M.txt");
  CreateSMatrix(&N, "TestData_N.txt");
  cout << "稀疏矩阵创建结束" << endl;

  cout << "M=" << endl;
  PrintSMatrix(M);

  cout << "N=" << endl;
  PrintSMatrix(N);

  RLSMatrix Temp;
  cout << "复制M到Temp" << endl;
  CopySMatrix(M, &Temp);

  cout << "Temp=" << endl;
  PrintSMatrix(Temp);

  RLSMatrix Q1;
  cout << "M与N加法运算" << endl;
  AddSMatrix(M, N, &Q1);

  cout << "Q1=" << endl;
  PrintSMatrix(Q1);

  RLSMatrix Q2;
  cout << "乘法运算" << endl;
  MultSMatrix(M, N, &Q2);

  cout << "Q2=" << endl;
  PrintSMatrix(Q2);

  RLSMatrix T1;
  cout << "转置操作" << endl;
  TransposeSMatrix(M, &T1);

  cout << "T1=" << endl;
  PrintSMatrix(T1);

  return 0;
}