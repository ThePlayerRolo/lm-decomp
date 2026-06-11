#ifndef _80009638_H_
#define _80009638_H_

#include <types.h>

u32 fn_80009638();

//This seems to be a common use of fn_80009638 that happens to cast it to s32
inline s32 fn_80009638C_Modulate(s32 val) {
    return fn_80009638() % val;
}
#endif
