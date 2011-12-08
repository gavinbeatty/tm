/**
tm Copyright 2010, 2011 Gavin Beatty <gavinbeatty@gmail.com>.
All rights reserved.

New BSD License

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  Neither the name of the tm project owners nor the names of its contributors may
  be used to endorse or promote products derived from this software without
  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
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
