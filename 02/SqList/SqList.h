#include "../../Status.h"
#include <iostream>
using namespace std;

#define LISTINCREMENT 10
#define LIST_INIT_SIZE 10

typedef int ElemType;
typedef struct
{
  ElemType *elem; // 存储空间的基址
  int length;     // 当前长度
  int listsize;   // 当前分配的存储容量
} SqList;

// 初始化操作
Status InitList(SqList *L);

// 摧毁顺序表
Status DestoryList(SqList *L);

// 清空顺序表
Status ClearList(SqList *L);

// 判断顺序表是否为空
Status ListEmpty(SqList L);

// 获取顺序表的长度
Status ListLength(SqList L);

// 用e返回顺序表中第i个元素的值
Status GetElem(SqList L, int i, ElemType *e);

// 返回顺序表中第1个与e满足compare()关系的数据元素
Status LocateElem(SqList L, ElemType e, Status(Compare)(ElemType, ElemType));

// 插入操作
Status ListInsert(SqList *L, int i, ElemType e);

// 删除操作
Status ListDelete(SqList *L, int i, ElemType *e);

// 遍历
Status ListTraverse(SqList L);
