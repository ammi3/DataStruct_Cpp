#include "../../Status.h"
#include <iostream>

using namespace std;

typedef struct {
    int ArrivedTime;    // 客户到达时间
    int Duration;       // 办理业务所需的时间
    int Count;          // 此变量记录来到每个队列的客户是第几个【教材中无此变量，增加此变量的目的是观察排队状况。】
} QElemType;            //队列的数据元素类型

// 队列元素结构
typedef struct QNode {
    QElemType data;
    struct QNode* next;
} QNode, * QueuePtr;

// 队列结构
typedef struct {
    QueuePtr front;     // 队头指针
    QueuePtr rear;      // 队尾指针
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