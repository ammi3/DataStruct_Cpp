#include "../../Status.h"
#include <iostream>
using namespace std;

#define STACK_INIT_SIZE 100 // 存储空间的初始分配量
#define STACKINCREMENT 10   // 存储空间的增量

typedef int SElemType;
typedef struct
{
  SElemType *base;
  SElemType *top;
  int stacksize; // 当时
} SqStack;

// 初始化栈
Status InitStack(SqStack *S);

// 销毁栈
Status DestoryStack(SqStack *S);

// 置空
Status ClearStack(SqStack *S);

// 判空
Status StackEmpty(SqStack S);

// 计数
Status StackLength(SqStack S);

// 栈顶元素
Status GetTop(SqStack S, SElemType *e);

// 插入
Status Push(SqStack *S, SElemType e);

// 弹出
Status Pop(SqStack *S, SElemType *e);

// 遍历
void StackTraverse(SqStack S);
