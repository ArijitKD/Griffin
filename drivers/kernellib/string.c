#include "string.h"

unsigned int strlength(const char *string)
{
  unsigned int i=0;
  while (string[i++]);
  return i-1;
}
