/* XXX lean and mean? own definitions of GetTickCountXX? */
#include <windows.h>

#include <tm/timespec.h>

int tm_monotonic(struct tm_timespec_t* tspec)
{
    assert(tspec);
#if TM_HAVE_WINDOWS_GETTICKCOUNT64
    uint64_t ms = GetTickCount64();
#else
    uint32_t ms = GetTickCount();
#endif
    tspec->tv_sec = ms / 1000;
    tspec->tv_nsec = (ms - (tspec->tv_sec * 1000)) * 1000000;
    return 0;
}

