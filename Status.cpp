#include "Status.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h> // 提供宏va_list、va_start、va_arg、va_end
#include <ctype.h>  // 提供isprint原型

void Wait(long time)
{
  double i;

  if (time < 0)
  {
    time = -time;
  }

  for (i = 0.01; i <= 100000.0 * time; i += 0.01)
  {
    // 空循环
  }
}

int ReadData(FILE *fp, char *format, ...)
{
  int *i;   // 存储读取到的整型
  float *f; // 存储读取到的浮点型
  char *ch; // 存储读取到的字符型
  char *s;  // 存储读取到的字符串型

  int n; // 遍历存储字符串的字符数组

  int len; // 格式串format的长度
  int k;   // 遍历格式串时的游标

  int tmp; // 暂存从文件中读取到的字符

  va_list ap; // 可变参数指针，指向存储数据的变量

  // 累计成功读取到的字符数
  int count = 0;

  /*
     * 获取格式串的长度
     * 这里预设格式串仅由简单
     */
  len = strlen(format);

  // ap指向首个可变参数
  va_start(ap, format);

  // 只遍历奇数索引，因为偶数索引下都是%
  for (k = 1; k <= len; k = k + 2)
  {
    // 跳过所有非西文字符
    while ((tmp = getc(fp)) != EOF)
    {
      // 遇到首个西文字符，将此西文字符重新放入输入流
      if ((tmp >= 0 && tmp <= 127))
      {
        ungetc(tmp, fp);
        break;
      }
    }

    // 如果已读到文件结尾，结束读取
    if (tmp == EOF)
    {
      break;
    }

    // 遇到了"%c"，应该读取字符
    if (format[k] == 'c')
    {
      ch = va_arg(ap, char *);

      count += fscanf(fp, "%c", ch);
    }

    // 遇到了"%d"，应该读取整型
    if (format[k] == 'd')
    {
      i = va_arg(ap, int *);

      while ((tmp = getc(fp)) != EOF)
      {
        // 寻找整数区域
        if ((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+')
        {
          ungetc(tmp, fp);
          break;
        }
      }

      if (tmp != EOF)
      {
        count += fscanf(fp, "%d", i);
      }
    }

    // 读取浮点型，一律存储为double类型
    if (format[k] == 'f')
    {
      f = va_arg(ap, float *);

      while ((tmp = getc(fp)) != EOF)
      {
        if ((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+' || tmp == '.')
        {
          ungetc(tmp, fp);
          break;
        }
      }

      if (tmp != EOF)
      {
        count += fscanf(fp, "%f", f);
      }
    }

    // 读取字符串
    if (format[k] == 's')
    {
      s = va_arg(ap, char *);

      n = 0;

      // 查找排除空格的可打印字符
      while ((tmp = getc(fp)) != EOF && (!isprint(tmp) || tmp == ' '))
      {
      }

      // 如果未到文件结尾
      if (!feof(fp))
      {

        // 将上面读到的字符重新放入流中
        ungetc(tmp, fp);

        while ((tmp = getc(fp)) != EOF)
        {
          // 存储排除空格的可打印字符
          if (isprint(tmp) && tmp != ' ')
          {
            s[n++] = tmp;
          }
          else
          {
            ungetc(tmp, fp);
            break;
          }
        }

        count++;
      }

      // 字符串最后一个字符为空字符
      s[n] = '\0';
    }
  } // for

  va_end(ap);

  return count;
}
