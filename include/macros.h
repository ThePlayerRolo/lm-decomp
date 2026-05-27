#ifndef LM_MACROS_H
#define LM_MACROS_H

#include <dolphin/macros.h>

#define ARRAY_COUNT(arr) (int)(sizeof(arr) / sizeof(arr[0]))

#define dummy_float_data() \
    static f32 dummy_float_data[6] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

#define FLAG_ON(V, F)    (((V) & (F)) == 0)
#define FLAG_OFF(V, F)   (((V) & (F)) != 0)

#define ALIGN_PREV(u, align) (u & (~(align - 1)))
#define ALIGN_NEXT(u, align) ((u + (align - 1)) & (~(align - 1)))
#define IS_ALIGNED(X, N)     (((X) & ((N) - 1)) == 0)
#define IS_NOT_ALIGNED(X, N) (((X) & ((N) - 1)) != 0)

#endif
