#include "math.h"

int roundint(float n)
{
  if ((n-(int)n)>0.5)
    return n+1;
  else
    return n;
}
