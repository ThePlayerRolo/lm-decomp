#ifndef KOGA_MATH_UTIL_H_
#define KOGA_MATH_UTIL_H_

#include <types.h>

namespace Koga {
    //It seems that Koga wrote his own implementation
    f32 absF(f32 x) {
        if (x > 0.0f) return x;
        return -x;
    }
};

#endif
