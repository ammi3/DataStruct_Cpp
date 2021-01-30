#include "LString.h"

/**
 * 初始化
 */
Status StrAssign(LString *T, const char *chars)
{
    Chunk *r;
    int len = (int)strlen(chars);
    if (len == 0)
    {
        (*T).head = NULL;
        (*T).tail = NULL;
        (*T).curlen = 0;
        return OK;
    }

    int m = len / CHUNKSIZE; // 计算填满的块
    int n = len % CHUNKSIZE; // 若存在未填满的块，则计算该块内有效元素的数量
    if (n != 0)
        m++;
    for (int i = 1; i <= m; i++)
    {
        r = (Chunk *)malloc(sizeof(Chunk));
        if (r == NULL)
            return ERROR;
        r->next = NULL;
        if (i == 1)
        {
            (*T).head = (*T).tail = r;
        }
        else
        {
            (*T).tail->next = r;
            (*T).tail = r;
        }
    }
    r = (*T).head;
    int i = 0, j = 0;
    // 赋值
    while (j < len)
    {
        r->ch[i] = chars[j];
        i = (i + 1) % CHUNKSIZE;
        if (i == 0)
            r = r->next;
        j++;
    }
    // 未填满的块
    if (n != 0)
    {
        while (i < CHUNKSIZE)
        {
            (*T).tail->ch[i] = '\0';
            i++;
        }
    }
    (*T).curlen = len;
    return OK;
}

/**
 * 销毁
 */
Status DestoryStr(LString *S)
{
    return OK;
}

/**
 * 清空
 */
Status ClearStr(LString *S)
{
    Chunk *cur = (*S).head;
    Chunk *next;
    while (cur != NULL)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    (*S).head = NULL;
    (*S).tail = NULL;
    (*S).curlen = 0;
    return OK;
}

/**
 * 判空
 */
Status StrEmpty(LString S)
{
    return S.curlen == 0 ? true : false;
}

/**
 * 计数
 */
int StrLength(LString S)
{
    return S.curlen;
}

/**
 * 求子串
 */
Status SubStr(LString *Sub, LString S, int pos, int len)
{
    Chunk *r, *p;
    if (pos < 1 || pos > S.curlen || len < 0 || pos + len - 1 > S.curlen)
        return ERROR;
    if (len == 0)
    {
        (*Sub).head = NULL;
        (*Sub).tail = NULL;
        (*Sub).curlen = 0;
        return OK;
    }

    int m = len / CHUNKSIZE;
    int n = len % CHUNKSIZE;
    if (n != 0)
        m++;

    for (int i = 1; i <= m; i++)
    {
        r = (Chunk *)malloc(sizeof(Chunk));
        if (r == NULL)
            return ERROR;
        r->next = NULL;
        if (i == 1)
        {
            (*Sub).head = (*Sub).tail = r;
        }
        else
        {
            (*Sub).tail->next = r;
            (*Sub).tail = r;
        }
    }

    for (int j = 1, p = S.head; pos > j * CHUNKSIZE; j++, p = p->next);
    r = (*Sub).head;
    int i = 0;
    int j = (pos - 1) % CHUNKSIZE;
    int count = 0;
    while (count < len)
    {
        r->ch[i] = p->ch[j];
        i = (i + 1) % CHUNKSIZE;
        if (i == 0)
            r = r->next;
        j = (j + 1) % CHUNKSIZE;
        if (j == 0)
            p = p->next;
        count++;
    }
    if (n != 0)
    {
        while (i < CHUNKSIZE)
        {
            (*Sub).tail->ch[i] = '\0';
            i++;
        }
    }
    (*Sub).curlen = len;
    return OK;
}

/**
 * 查找
 */
int Index(LString S, LString T, int pos)
{
    LString Sub;
    if (pos < 1 || pos > S.curlen || StrEmpty(T))
        return 0;
    int s = S.curlen;
    int t = T.curlen;
    int i = pos;
    while (i + t - 1 <= s)
    {
        SubStr(&Sub, S, i, t);
        if (StrCompare(Sub, T) != 0)
        {
            ++i;
        }
        else
        {
            return i;
        }
    }
    return 0;
}

/**
 * 插入
 */
Status StrInsert(LString *S, int pos, LString T)
{
}
/**
 * 删除
 */
Status StrDelete(LString *S, int pos, int len)
{
}

/**
 * 比较
 */
Status StrCompare(LString S, LString T)
{
}

/**
 * 替换
 */
Status Replace(LString *S, LString T, LString V)
{
}

/**
 * 串连接
 */
Status Concat(LString *T, LString S1, LString S2)
{
}