/* vi: set ft=c expandtab: */
#ifndef TM_TM_H_
#define TM_TM_H_

#include <tm/config.h>

#include <tm/impl/plat.h>
#include <tm/timespec.h>

DECL_BEGIN_C

int tm_monotonic(struct tm_timespec_t* tspec);

double tm_timespec_to_double(const struct tm_timespec_t* tspec);
float tm_timespec_to_float(const struct tm_timespec_t* tspec);

DECL_END_C
#endif
