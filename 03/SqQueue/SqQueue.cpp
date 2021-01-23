#include "SqQueue.h"

/**
 * 初始化
 */
Status InitQueue(SqQueue *Q)
{
  if (Q == NULL)
    return ERROR;
  (*Q).base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
  if (!(*Q).base)
    return ERROR;
  (*Q).front = (*Q).rear = 0;
  return OK;
}

/**
 * 销毁
 */
Status DestoryQueue(SqQueue *Q)
{
  if (Q == NULL)
    return ERROR;
  if ((*Q).base)
    free((*Q).base);
  (*Q).base = NULL;
  (*Q).front = (*Q).rear = 0;
  return OK;
}

/**
 * 置空
 */
Status ClearQueue(SqQueue *Q)
{
  if (Q == NULL || (*Q).base == NULL)
    return ERROR;
  (*Q).front = (*Q).rear = 0;
  return OK;
}

/**
 * 判空
 */
Status QueueEmpty(SqQueue Q)
{
  if (Q.front == Q.rear)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * 计数
 */
int QueueLength(SqQueue Q)
{
  if (Q.base == NULL)
    return ERROR;
  return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

/**
 * 获取队头
 */
Status GetHead(SqQueue Q, QElemType *e)
{
  if (Q.base == NULL || Q.front == Q.rear)
    return ERROR;
  *e = Q.base[Q.front];
  return OK;
}

/**
 * 入队
 */
Status EnQueue(SqQueue *Q, QElemType e)
{
  if (Q == NULL || (*Q).base == NULL)
    return ERROR;
  if (((*Q).rear + 1) % MAXQSIZE == (*Q).front)
    return ERROR;
  (*Q).base[(*Q).rear] = e;
  (*Q).rear = ((*Q).rear + 1) % MAXQSIZE;
  return OK;
}

/**
 * 出队
 */
Status DeQueue(SqQueue *Q, QElemType *e)
{
  if (Q == NULL || (*Q).base == NULL)
    return ERROR;
  if ((*Q).front == (*Q).rear)
    return ERROR;
  *e = (*Q).base[(*Q).front];
  (*Q).front = ((*Q).front + 1) % MAXQSIZE;
  return OK;
}

/**
 * 遍历
 */
void QueueTravese(SqQueue Q)
{
  if (Q.base == NULL)
    return;
  for (int i = Q.front; i != Q.rear; i = (i + 1) % MAXQSIZE)
  {
    cout << Q.base[i] << " ";
  }
  cout << endl;
}

int main()
{
  SqQueue Q;
  QElemType e;

  cout << "开始初始化循环队列" << endl;
  InitQueue(&Q);
  cout << "初始循环化队列结束" << endl;

  QueueEmpty(Q) ? printf("循环队列为空！\n") : printf("循环队列不为空！\n");

  cout << "开始插入元素" << endl;
  for (int i = 1; i <= 6; i++)
  {
    EnQueue(&Q, i);
    printf("█ 元素 \"%2d\" 入队Q...\n", i);
  }
  cout << "插入元素结束" << endl;

  int length = QueueLength(Q);
  cout << "此时循环链表的长度为：" << length << endl;

  cout << "此时循环链表内的元素依次为：";
  QueueTravese(Q);

  cout << "出队" << endl;
  DeQueue(&Q, &e);
  cout << "出队元素为：" << e << endl;

  cout << "此时循环链表内的元素依次为：";
  QueueTravese(Q);

  return OK;
}