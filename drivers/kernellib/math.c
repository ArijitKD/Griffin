#include "math.h"

int roundint(float n)
{
    if (n >= 0)
        return ((n - (int)n) >= 0.5) ? (n + 1) : n;
    else
        return (((int)n - n) >= 0.5) ? (n - 1) : n;
}
