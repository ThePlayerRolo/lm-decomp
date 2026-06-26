#include "Unsorted/800627D8.hpp"

void setLuigiAppearPoint(u32 apperPoint) {
    sGlobalLuigiAppearPoint = apperPoint;
}

u32 getLuigiAppearPoint() {
    u32 temp = sGlobalLuigiAppearPoint;
    sGlobalLuigiAppearPoint = 0;
    return temp;
}
