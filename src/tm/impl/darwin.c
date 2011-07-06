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

