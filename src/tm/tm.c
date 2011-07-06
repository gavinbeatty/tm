#include <tm/tm.h>

#include <assert.h>
#include <tm/timespec.h>

#if PLAT_OS_DARWIN
# include <tm/impl/darwin.c>
#elif PLAT_OS_UNIX /* && !PLAT_OS_DARWIN */
# include <tm/impl/unix.c>
#elif PLAT_OS_WIN
# include <tm/impl/windows.c>
#else
# error "Platform not supported!"
#endif

double tm_timespec_to_double(const struct tm_timespec_t* tspec)
{
    assert(NULL != tspec);
    return (tspec->tv_sec + (tspec->tv_nsec * 0.000000001));
}
float tm_timespec_to_float(const struct tm_timespec_t* tspec)
{
    assert(NULL != tspec);
    return (tspec->tv_sec + (tspec->tv_nsec * 0.000000001f));
}

