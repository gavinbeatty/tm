#ifndef TM_IMPL_PLAT_H_
#define TM_IMPL_PLAT_H_

#if 0
if PLAT_OS_DARWIN
 include <tm/impl/darwin.h>
elif PLAT_OS_UNIX /* && !PLAT_OS_DARWIN */
 include <tm/impl/unix.h>
elif PLAT_OS_WIN
#endif // 0
/* only windows needs this header */
#if PLAT_OS_WIN
# include <tm/impl/windows.h>
#endif

#endif /* TM_IMPL_PLAT_H_ */
