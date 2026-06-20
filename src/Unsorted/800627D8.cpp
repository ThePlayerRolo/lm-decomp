#include "Unsorted/800627D8.hpp"

u32 getLuigiAppearPoint() {
    u32 temp = sGlobalLuigiAppearPoint;
    sGlobalLuigiAppearPoint = 0;
    return temp;
}
