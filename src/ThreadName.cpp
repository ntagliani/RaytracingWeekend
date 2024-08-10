#include "ThreadName.h"

#ifdef WIN32
#include <windows.h>

#include <processthreadsapi.h>
#endif

void setThreadName(const char* name)
{
#ifdef WIN32
    wchar_t buffer[64];
    size_t converted = 0;
    mbstowcs_s(&converted, buffer, name, 64);
    SetThreadDescription(GetCurrentThread(), buffer);
#endif
}
