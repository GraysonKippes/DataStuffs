#include "CmpFunc.h"

int cmpFuncInt(const void *const pA, const void *const pB)
{
    if (!pA || !pB) {
        return -2;
    }

    const int a = *(int *)pA;
    const int b = *(int *)pB;
    if (a < b) {
        return -1;
    }
    else if (a > b) {
        return 1;
    }
    else {
        return 0;
    }
}