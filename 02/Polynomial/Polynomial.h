#include "ELinkList.h"

typedef ELinkList Polynomial;

// 创建
void CreatPolyn(Polynomial *P, int m);

// 销毁
void DestroyPolyn(Polynomial *P);

// 计数
int PolynLength(Polynomial P);

// 加法
void AddPolyn(Polynomial *Pa, Polynomial *Pb);

// 减法
void SubtractPolyn(Polynomial *Pa, Polynomial *Pb);

// 比较
int Cmp(ElemType c1, ElemType c2);
