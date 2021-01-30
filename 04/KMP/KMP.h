#include "SString.h"

// 从pos处开始搜索模式串T在主串S中首次出现的位置
int Index_KMP(SString S, SString T, int pos, int next[]);

// 计算模式串的“失配数组”，KMP算法
void get_next(SString T, int next[]);

/// 计算模式串的“失配数组”，KMP算法，优化版本
void get_nextVal(SString T, int nextVal[]);