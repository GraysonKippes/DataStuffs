#include "BHeap.h"

#ifdef unix
#include <unistd.h>
size_t getPageSize(void)
{
    return (size_t)sysconf(_SC_PAGESIZE);
}
#elif _WIN32
#include <windows.h>
size_t getPageSize(void)
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    return (size_t)systemInfo.dwPageSize;
}
#else
size_t getPageSize(void)
{
    return 0LLU;
}
#endif