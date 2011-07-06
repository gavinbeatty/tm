#include <tm/tm.h>

#include <errno.h>

#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    struct tm_timespec_t tspec;
    double fst = -1.0;
    double snd = -2.0;
    if (-1 == tm_monotonic(&tspec)) {
        fprintf(stderr, "tm_monotonic 1st failed: %s\n", strerror(errno));
        return 1;
    }
    fst = tm_timespec_to_double(&tspec);
    printf("1st: %lf\n", fst);

    if (-1 == tm_monotonic(&tspec)) {
        fprintf(stderr, "tm_monotonic 2nd failed: %s\n", strerror(errno));
        return 1;
    }
    snd = tm_timespec_to_double(&tspec);
    printf("2nd: %lf\n", snd);

    return snd >= fst;
}

