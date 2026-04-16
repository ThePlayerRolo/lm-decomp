//https://github.com/doldecomp/sms/blob/main/include/PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stddef.h
#ifndef _STDDEF_H_
#define _STDDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __INTELLISENSE__
typedef unsigned int size_t;
typedef int ptrdiff_t;
#else
typedef unsigned long size_t;
typedef long ptrdiff_t;
#endif

#define offsetof(type, member) ((size_t)&(((type*)0)->member))

#ifndef NULL
#define NULL 0
#endif

#ifdef __cplusplus
};
#endif

#endif
