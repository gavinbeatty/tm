#ifndef TM_TIMESPEC_H_
#define TM_TIMESPEC_H_

#include <tm/config.h>

# include <time.h>
#if PLAT_OS_WIN
  struct tm_timespec_t {
      time_t tv_sec;
      long tv_nsec;
  };
#else
# define tm_timespec_t timespec
#endif

#endif /* TM_TIMESPEC_H_ */
