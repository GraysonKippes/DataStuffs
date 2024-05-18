// Author: Grayson Kippes
// Date: 4/24/2024
// Description: function pointer definition for comparison functions.

#ifndef DATASTUFF_CMPFUNC_H
#define DATASTUFF_CMPFUNC_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// Function signature for any function that compares two objects.
// The function must return -1 to indicate that *pA is less than *pB.
// The function must return 0 to indicate that *pA is equal to *pB.
// The function must return 1 to indicate that *pA is greater than *pB.
// Any other return value will be treated as an error.
typedef int (*CmpFunc)(const void *const pA, const void *const pB);

// Default compare function.
// Casts pA and pB to int pointers and dereferences then compares them normally.
int cmpFuncInt(const void *const pA, const void *const pB);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // DATASTUFF_CMPFUNC_H
