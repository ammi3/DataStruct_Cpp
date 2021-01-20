#include "Polynomial.h"

// 创建
void CreatPolyn(Polynomial *P, int m)
{
  ElemType e;
  Position head, q;
  Link s;

  InitList(P);
  head = GetHead(*P); //获取头指针
  e.coef = 0.0f;
  e.expm = -1;
  SetCurElem(head, e);

  cout << "请输入" << m << "个元素" << endl;

  for (int i = 1; i <= m; i++)
  {
    cout << "请输入第" << i << "组系数和指数" << endl;
    scanf("%f%d", &(e.coef), &(e.expm));

    if (LocateElem(*P, e, &q, Cmp) == false && q != NULL)
    {
      if (MakeNode(&s, e) == OK)
      {
        InsFirst(P, q, s);
      }
    }
  }
}

// 销毁
void DestroyPolyn(Polynomial *P)
{
  DestoryList(P);
}

// 计数
int PolynLength(Polynomial P)
{
  return ListLength(P);
}

// 加法
void AddPolyn(Polynomial *Pa, Polynomial *Pb)
{
  Position headA, headB;
  Position curA, curB;
  ElemType a, b;
  float sum;

  headA = GetHead(*Pa);
  headB = GetHead(*Pb);

  curA = NextPos(*Pa, headA);
  curB = NextPos(*Pb, headB);

  while (curA && curB)
  {
    a = GetCurElem(curA);
    b = GetCurElem(curB);

    switch (Cmp(a, b))
    {
    case -1:
      headA = curA;
      curA = NextPos(*Pa, curA);
      break;

    case 0:
      sum = a.coef + b.coef;
      if (sum != 0.0)
      {
        curA->data.coef = sum;
        headA = curA;
      }
      else
      {
        DelFirst(Pa, headA, &curA);
        FreeNode(&curA);
      }
      DelFirst(Pb, headB, &curB);
      FreeNode(&curB);
      curA = NextPos(*Pa, headA);
      curB = NextPos(*Pb, headB);
      break;
    case 1:
      DelFirst(Pb, headB, &curB);
      InsFirst(Pa, headA, curB);
      headA = NextPos(*Pa, headA);
      curB = NextPos(*Pb, headB);
      break;
    }
  }

  if (curB != NULL)
  {
    Append(Pa, curB);
  }

  // 释放Pb头结点
  FreeNode(&headB);

  // 设置Pb为销毁状态
  (*Pb).head = (*Pb).tail = NULL;
  (*Pb).len = 0;
}

/*
 * 比较
 *
 * 比较c1项和c2项指数大小。
 */
int Cmp(ElemType c1, ElemType c2)
{
  // 计算指数差
  int i = c1.expm - c2.expm;

  if (i < 0)
  {
    return -1;
  }
  else if (i == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int main()
{
  Polynomial Pa, Pb;

  cout << "开始创建一元多项式Pa" << endl;
  CreatPolyn(&Pa, 3);
  cout << "Pa创建结束" << endl;

  cout << "开始创建一元多项式Pb" << endl;
  CreatPolyn(&Pb, 3);
  cout << "Pb创建结束" << endl;

  printf("█ Pa 的项数为 %d ，Pb 的项数为 %d\n", PolynLength(Pa), PolynLength(Pb));

  cout << "Pa与Pb相加" << endl;
  AddPolyn(&Pa, &Pb);
  printf("█ Pa 的项数为 %d\n", PolynLength(Pa));
  return 0;
}