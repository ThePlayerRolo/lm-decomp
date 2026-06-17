#include "jaudio/ja_calc.h"

#include "jaudio/ja_calc.h"
#include <math.h>

#define SINTABLE_LENGTH (257)
static f32 SINTABLE[SINTABLE_LENGTH];

/**
 * @TODO: Documentation
 */
f32 sqrtf2(f32 x)
{
	return std::sqrtf(x);
}

/**
 * @TODO: Documentation
 */
void Jac_InitSinTable()
{
	for (u32 i = 0; i < SINTABLE_LENGTH; i++) {
		SINTABLE[i] = sinf(i * HALF_PI / 256.0f);
	}
}

/**
 * @TODO: Documentation
 */
f32 sinf3(f32 x)
{
	return SINTABLE[(int)(256.0f * x)];
}
