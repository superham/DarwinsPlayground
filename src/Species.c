#include "Species.h"

#define DEFAULT_STATS 25
#define DEFAULT_LIFESPAN (int)((((float)DEFAULT_STATS) / 100.0f) * (((float)DEFAULT_STATS) / 100.0f) * 80.0f)

#include <stdlib.h>
#include <time.h>

void Species_init(Species* species)
{
	srand(time(NULL));
	species->strength = DEFAULT_STATS;
	species->dexterity = DEFAULT_STATS;
	species->resourcefulness = DEFAULT_STATS;
	species->tenacity = DEFAULT_STATS;
	species->lifespan = DEFAULT_LIFESPAN;
	species->fertility = 1;
}

void Species_growRelative(Species* species, int d_str, int d_dex, int d_sus, int d_res)
{
	species->strength += d_str;
	species->dexterity += d_dex;
	species->resourcefulness += d_res;
	species->tenacity += d_sus;

	float _lifespan;
	_lifespan = (float)(species->strength) / 100.0f;
	_lifespan *= ((float)(species->tenacity) / 100.0f) * 80.0f;

	species->lifespan = (unsigned)_lifespan;
}
