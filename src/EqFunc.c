#include "EqFunc.h"

#include <stddef.h>

bool eqFuncInt(void *const pA, void *const pB)
{
    if(!pA || !pB) {
        return false;
    }
    return *(int *)pA == *(int *)pB;
}