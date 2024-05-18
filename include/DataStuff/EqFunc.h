// Author: Grayson Kippes
// Date: 5/12/2024
// Description: function pointer definition for equality functions.

#ifndef DATASTUFF_EQFUNC_H
#define DATASTUFF_EQFUNC_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdbool.h>

// Returns true if the two objects are equal, false otherwise.
typedef bool (*EqFunc)(void *const pA, void *const pB);

bool eqFuncInt(void *const pA, void *const pB);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // DATASTUFF_EQFUNC_H