#include "Region.h"
#include "Species.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define TAU (double)(12 * REGION_MAX_STAT_LEVEL * REGION_MAX_STAT_LEVEL * REGION_MAX_STAT_LEVEL)
#define E 2.718281828459

void Region_init(Region* region, SDL_Renderer* renderer, const char* texfile, int baseTemp, int baseTerr, int baseHumid)
{
	srand(time(NULL));
	Square_create(&(region->square), renderer, texfile, 0, 0, REGION_TILE_SIZE, REGION_TILE_SIZE);

	region->maxPopulation = 10000L;
	region->randDanger = rand()%1;
	region->population = 0L;
	region->temperature = baseTemp;
	region->humidity = baseHumid;
	region->terrain = baseTerr;
}

void Region_displayAt(Region* region, int x, int y)
{
	(region->square).bounds.x = x;
	(region->square).bounds.y = y;
}

unsigned Region_update(Region* region, int mx, int my, int clicked)
{
	int c;
	
	if(Square_intersectsPoint(&(region->square), mx, my))
	{
		if(clicked)
		{
			c = (int)(((double)(region->maxPopulation - region->population) / (double)(region->maxPopulation)) * 0x00000088);
			(region->square).color = (c << 16) | c | 0x00008800;
			
			if(region->population == 0L)
				region->population = 100L;

			return CLICK_ON_REGION;
		}
		else
		{
			
			c = (int)(((double)(region->maxPopulation - region->population) / (double)(region->maxPopulation)) * 0x000000bb);
			(region->square).color = (c << 16) | c | 0x0000bb00;

			return HOVER_ON_REGION;
		}
	}
	else
	{

		
		c = (int)(((double)(region->maxPopulation - region->population) / (double)(region->maxPopulation)) * 255.0);
		(region->square).color = (c << 16) | c | 0x0000ff00;
		return 0;
	}
}

void Region_growPop(Region* region, Species* species)
{
	double resourcei,dangeri,safetyi, rateG, rateD, grow, decay, seconds;
	static long time = 0;
	if(region->population > 0)
	{

		seconds = time/60;
		resourcei = ((region->temperature)+(region->terrain)+(species->resourcefulness)+(region->humidity))/(double)400;
		dangeri = ((region->terrain)/(double)100) + (abs(region->temperature - 50)/(double)50) + region->randDanger;
		safetyi = ((species->strength)+(species->dexterity)+(species->tenacity))/(double)300;
		time ++;

		if(region->population >= region->maxPopulation || region->population < 0L)
			region->population = region->maxPopulation;
		else
		{
			rateG = resourcei * dangeri *safetyi;
			rateD = (region->maxPopulation - region->population)/(region->maxPopulation) + region->randDanger + (region->terrain)/100.0;
			grow = 10 * pow(E,((rateG*seconds)/6));
			decay = -2 * pow(E,((rateD*seconds)/6));
			if((double)region->population+grow+decay<0){region->population=0;}
			else{region->population += grow+decay;}
		}
	}
}

void Region_render(Region* region, SDL_Renderer* renderer)
{
	Square_render(&(region->square), renderer);
}

void Region_destroy(Region* region)
{
	region->population = 0L;
	Square_destroy(&(region->square));
}
