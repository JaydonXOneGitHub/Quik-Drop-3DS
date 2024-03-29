#ifndef VI3DSE
#define VI3DSE

#include "include/scoped_ptr.h"
#include "include/event.h"
#include "include/macros.h"
#include "citro2d.h"
#include "citro3d.h"
#include "include/tilemap.h"
#include "include/vector2.h"
#include <time.h>
#include <memory>
#include <math.h>
#include "include/aabb.h"

#define MAX_SPRITES   768
#define T_SCREEN_WIDTH  400
#define T_SCREEN_HEIGHT 240
#define B_SCREEN_WIDTH  320
#define B_SCREEN_HEIGHT 240

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

typedef struct
{
	C2D_Sprite spr;
	float dx, dy = 0; // velocity
} Sprite;

#endif