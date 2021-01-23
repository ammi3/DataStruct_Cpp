#include "../../Status.h"
#include <iostream>

using namespace std;

typedef int QElemType;
typedef struct QNode
{
  QElemType data;
  struct QNode *next;
} QNode, *QueuePtr;
typedef struct
{
  QueuePtr front; // 队头指针
  QueuePtr rear;  // 队尾指针
} LinkQueue;

// 初始化
Status InitQueue(LinkQueue *Q);

// 摧毁队列
Status DestoryQueue(LinkQueue *Q);

// 置空
Status ClearQueue(LinkQueue *Q);

// 判空
Status QueueEmpty(LinkQueue Q);

// 计数
int QueueLength(LinkQueue Q);

// 获取队头元素
Status GetHead(LinkQueue Q, QElemType *e);

// 入队
Status EnQueue(LinkQueue *Q, QElemType e);

// 出队
Status DeQueue(LinkQueue *Q, QElemType *e);

// 遍历
void QueueTraverse(LinkQueue Q);