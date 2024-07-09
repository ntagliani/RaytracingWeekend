#pragma once

#ifdef WIN_PLATFORM

#define SIZE_T_FMT "llu"

#else
#ifdef UNIX_PLATFORM
#define SIZE_T_FMT "lu"
#else
#ifdef APPLE_PLATFORM
#define SIZE_T_FMT "lu"
#endif
#endif
#endif
