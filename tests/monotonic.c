#include <tm/tm.h>

#include <errno.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    struct tm_timespec_t tspec;
    if (0 != tm_monotonic(&tspec)) {
        fprintf(stderr, "tm_monotonic 1st failed: %s\n", strerror(errno));
        return 1;
    }
    printf("1st: %lf\n", tm_timespec_to_double(&tspec));

    if (0 != tm_monotonic(&tspec)) {
        fprintf(stderr, "tm_monotonic 2nd failed: %s\n", strerror(errno));
        return 1;
    }
    printf("2nd: %lf\n", tm_timespec_to_double(&tspec));

    return 0;
}

