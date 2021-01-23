#include "../../Status.h"
#include <iostream>
using namespace std;

#define MAXQSIZE 100
typedef int QElemType;
typedef struct
{
  QElemType *base; // 初始化的动态分配内存
  int front;       // 头指针
  int rear;        // 尾指针
} SqQueue;

Status InitQueue(SqQueue *Q);

// 销毁
Status DestoryQueue(SqQueue *Q);

// 置空
Status ClearQueue(SqQueue *Q);

// 判空
Status QueueEmpty(SqQueue Q);

// 计数
int QueueLength(SqQueue Q);

// 获取队头
Status GetHead(SqQueue Q, QElemType *e);

// 入队
Status EnQueue(SqQueue *Q, QElemType e);

// 出队
Status DeQueue(SqQueue *Q, QElemType *e);

// 遍历
void QueueTravese(SqQueue Q);