#include "LinkQueue.h"

/**
 * 初始话队列
 */
Status InitQueue(LinkQueue *Q)
{
  if (Q == NULL)
    return ERROR;
  (*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
  if (!(*Q).front)
    return ERROR;
  (*Q).front->next = NULL;
  return OK;
}

/**
 * 摧毁队列
 */
Status DestoryQueue(LinkQueue *Q)
{
  if (Q == NULL)
    return ERROR;
  while ((*Q).front)
  {
    (*Q).rear = (*Q).front->next;
    free((*Q).front);
    (*Q).front = (*Q).rear;
  }
  return OK;
}

/**
 * 清空队列
 */
Status ClearQueue(LinkQueue *Q)
{
  if (Q == NULL)
    return ERROR;
  (*Q).rear = (*Q).front->next;
  while ((*Q).rear)
  {
    (*Q).front->next = (*Q).rear->next;
    free((*Q).rear);
    (*Q).rear = (*Q).front->next;
  }
  return OK;
}

/**
 * 判断是否为空
 */
Status QueueEmpty(LinkQueue Q)
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
int QueueLength(LinkQueue Q)
{
  int length = 0;
  QueuePtr cur = Q.front;
  while (cur != Q.rear)
  {
    length++;
    cur = cur->next;
  }
  return length;
}

/**
 * 获取队头元素
 */
Status GetHead(LinkQueue Q, QElemType *e)
{
  if (Q.front == NULL || Q.front == Q.rear)
    return ERROR;
  QueuePtr cur = Q.front->next;
  *e = cur->data;
  return OK;
}

/**
 * 入队
 */
Status EnQueue(LinkQueue *Q, QElemType e)
{
  if (Q == NULL || (*Q).front == NULL)
    return ERROR;
  QueuePtr cur = (QueuePtr)malloc(sizeof(QNode));
  if (!cur)
    return ERROR;
  cur->data = e;
  cur->next = NULL;
  (*Q).rear->next = cur;
  (*Q).rear = cur;
  return OK;
}

/**
 * 出队
 */
Status DeQueue(LinkQueue *Q, QElemType *e)
{
  if (Q == NULL || (*Q).front == NULL || (*Q).front == (*Q).rear)
    return ERROR;
  QueuePtr cur = (*Q).front->next;
  *e = cur->data;
  (*Q).front->next = cur->next;
  if ((*Q).rear == cur)
    (*Q).rear = (*Q).front;
  free(cur);
  return OK;
}

/**
 * 遍历
 */
void QueueTraverse(LinkQueue Q)
{
  if (Q.front == NULL)
    return;
  QueuePtr cur = Q.front->next;
  while (cur != NULL)
  {
    printf("%d", cur->data);
    cur = cur->next;
  }
  cout << endl;
}