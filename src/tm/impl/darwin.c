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
#include <tm/tm.h>

#include <errno.h>
#include <sys/time.h>

#include <mach/mach_host.h>
#include <mach/mach_port.h>
#include <mach/clock_types.h>
#include <mach/clock.h>

#include <assert.h>

#include <tm/timespec.h>

int tm_monotonic(struct timespec *tp)
{
    // XXX if mach_timespec_t is the same as struct timespec, then don't bother
    // copying
    mach_timespec_t mach_tp;
    clock_serv_t clock_ref;
    host_name_port_t host_self = mach_host_self();
    // remember, never set errno = 0
    if (KERN_SUCCESS != host_get_clock_service(host_self, SYSTEM_CLOCK, &clock_ref)) {
        errno = EINVAL;
        return -1;
    }
    if (KERN_SUCCESS != clock_get_time(clock_ref, &mach_tp)) {
        errno = EINVAL;
        mach_port_deallocate(mach_task_self(), host_self);
        return -1;
    }
    tp->tv_sec = mach_tp.tv_sec;
    tp->tv_nsec = mach_tp.tv_nsec;
    mach_port_deallocate(mach_task_self(), host_self);
    mach_port_deallocate(mach_task_self(), clock_ref);
    return 0;
}

int tm_monotonic_resolution_nanos(void)
{
    clock_serv_t clock_ref;
    natural_t attr;
    mach_msg_type_number_t count = sizeof(attr);
    host_name_port_t host_self = mach_host_self();
    ipc_space_t task_self;
    if (KERN_SUCCESS != host_get_clock_service(host_self, SYSTEM_CLOCK, &clock_ref))
    {
        errno = EINVAL;
        return -1;
    }
    if (KERN_SUCCESS != clock_get_attributes(clock_ref, CLOCK_GET_TIME_RES, (clock_attr_t)&attr, &count))
    {
        errno = EINVAL;
        mach_port_deallocate(mach_task_self(), host_self);
        return -1;
    }
    task_self = mach_task_self();
    mach_port_deallocate(task_self, host_self);
    mach_port_deallocate(task_self, clock_ref);
    assert(sizeof(attr) >= count);
    assert(attr > 0);
    return attr;
}

