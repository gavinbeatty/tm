/* vi: set ft=c expandtab: */
#ifndef TM_TM_H_
#define TM_TM_H_

#include <tm/config.h>

#include <tm/impl/plat.h>
#include <tm/timespec.h>

DECL_BEGIN_C

/**
 * Get the current monotonic time, and set it in tspec.
 *
 * \warning Some platforms (Windows) do not have true monotonic time, and the
 * value will wrap after some time.
 *
 * Returns -1 on error. Check errno. EINVAL is used for unspecified error.
 */
int tm_monotonic(struct tm_timespec_t* tspec);

/**
 * Get the resolution of the monotonic timer used in tm_monotonic.
 *
 * \warning This is just a thin wrapper around the platform's provided method
 * for querying the resolution. Some platforms (e.g., Mac OS X) always provide
 * values that are much larger than the \e real resolution.
 *
 * Returns -1 on error. Check errno. EINVAL is used for unspecified error.
 */
int tm_monotonic_resolution_nanos(void);

/**
 * Convert the tspec (which has seconds and nanoseconds components) into
 * floating point.
 *
 * tspec cannot be NULL.
 */
double tm_timespec_to_double(const struct tm_timespec_t* tspec);
/// \sa tm_timespec_to_double
float tm_timespec_to_float(const struct tm_timespec_t* tspec);

DECL_END_C
#endif
