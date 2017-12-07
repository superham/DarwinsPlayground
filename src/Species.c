#include "Species.h"

#define DEFAULT_STATS 50
#define DEFAULT_LIFESPAN 10

void Species_init(Species* species)
{
	species->strength = DEFAULT_STATS;
	species->dexterity = DEFAULT_STATS;
	species->resourcefulness = DEFAULT_STATS;
	species->tenacity = DEFAULT_STATS;
	species->lifespan = DEFAULT_LIFESPAN;
	species->fertility = 1;

	species->d_hot = 0;
	species->d_cold = 0;
	species->d_arid = 0;
	species->d_mount = 0;
	species->d_forest = 0;
	species->evo_points = 0;
}

void Species_growRelative(Species* species, int d_str, int d_dex, int d_sus, int d_res)
{
	species->strength += d_str;
	species->dexterity += d_dex;
	species->resourcefulness += d_res;
	species->tenacity += d_sus;

	float _lifespan;
	_lifespan = (float)(species->strength) / 100.0f;
	_lifespan *= ((float)(species->tenacity) / 100.0f) * 240.0f;

	species->lifespan = (unsigned)_lifespan;
}
