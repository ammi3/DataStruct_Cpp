#include "Status.h"

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