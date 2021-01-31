#include <iostream>
#include <string.h>
#include "../../Status.h"
using namespace std;

#define CHUNKSIZE 3 // 块大小
//串的块链存储结构定义
typedef struct Chunk
{
    char ch[CHUNKSIZE]; // 当前块的内容
    struct Chunk *next; // 指向下一个块
} Chunk;

// 串的块链存储类型定义
typedef struct
{
    Chunk *head; // 串的头指针
    Chunk *tail; // 串的尾指针
    int curlen;  // 串的当前长度
} LString;

// 初始化
Status StrAssign(LString *T, const char *chars);

// 销毁
Status DestoryStr(LString *S);

// 清空
Status ClearStr(LString *S);

// 判空
Status StrEmpty(LString S);

// 计数
int StrLength(LString S);

// 求子串
Status SubStr(LString *Sub, LString S, int pos, int len);

// 查找
int Index(LString S, LString T, int pos);

// 插入
Status StrInsert(LString *S, int pos, LString T);

// 删除
Status StrDelete(LString *S, int pos, int len);

// 比较
Status StrCompare(LString S, LString T);

// 替换
Status Replace(LString *S, LString T, LString V);

// 串链接
Status Concat(LString *T, LString S1, LString S2);
