#ifndef GAME_REGION_H__
#define GAME_REGION_H__

#include "Square.h"
#include "Species.h"

#define REGION_MAX_STAT_LEVEL 100
#define REGION_TILE_SIZE 60

#define CLICK_ON_REGION 2
#define HOVER_ON_REGION 1

typedef struct {

	Square square;
	
	long maxPopulation;
	unsigned long population;

	int temperature;
	int terrain;
	int humidity;
	int randDanger;
} Region;

void Region_init(Region*, SDL_Renderer*, const char*, int, int, int);
void Region_displayAt(Region*, int, int);
unsigned Region_update(Region*, int, int, int);

void Region_growPop(Region*, Species*);
void Region_render(Region*, SDL_Renderer*);
void Region_destroy(Region*);

#endif /* GAME_REGION_H__ */
