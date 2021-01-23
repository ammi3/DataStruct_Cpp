#ifndef SQSTACK_H
#define SQSTACK_H

#include "../../Status.h"
#include <iostream>
using namespace std;

#define STACK_INIT_SIZE 100 // 存储空间的初始分配量
#define STACKINCREMENT 10   // 存储空间的增量

// 迷宫通道块的坐标
typedef struct
{
  int x; // 通道块的横、纵坐标定义
  int y;
} PosType;

/* 通道块信息，用于迷宫算法 */
typedef struct
{
  int ord;      // 通道块的“序号”
  PosType seat; // 通道块的“坐标位置”
  int di;       // 下一个应当访问的“方向”
} SElemType;

// 顺序栈元素结构
typedef struct
{
  SElemType *base; // 栈底指针
  SElemType *top;  // 栈顶指针
  int stacksize;   // 当前已分配的存储空间，以元素为单位
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

#endif
