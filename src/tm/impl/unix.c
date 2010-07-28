#include <tm/tm.h>

#include <time.h>

#include <assert.h>

#include <tm/timespec.h>

int tm_monotonic(struct tm_timespec_t* tspec)
{
    assert(tspec);
    return clock_gettime(CLOCK_MONOTONIC, tspec);
}

