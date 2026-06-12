#ifndef STATIC_DATA_H
#define STATIC_DATA_H

#include <version.h>

#if VERSION == VERSION_USA
extern u8 staticdata_usa_arc[];
#define STATIC_DATA staticdata_usa_arc
#else
extern u8 staticdata_arc[];
#define STATIC_DATA  staticdata_arc
#endif

#endif
