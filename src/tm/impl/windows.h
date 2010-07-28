#ifndef TM_IMPL_WINDOWS_H_
#define TM_IMPL_WINDOWS_H_

#if !PLAT_OS_WIN
# error "windows platform header included but not on windows!"
#endif

#if !TM_HAVE_WINDOWS_GETTICKCOUNT64
# warning "GetTickCount implementation wraps after ~50 days - BE CAREFUL!"
#endif

#endif /* TM_IMPL_WINDOWS_H_ */
