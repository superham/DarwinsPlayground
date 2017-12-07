#include "Region.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define TAU (double)(12 * REGION_MAX_STAT_LEVEL * REGION_MAX_STAT_LEVEL * REGION_MAX_STAT_LEVEL)

void Region_init(Region* region, SDL_Renderer* renderer, const char* texfile, int baseTemp, int baseTerr, int baseHumid)//Initalizes a region
{
	srand(time(NULL));

	Square_create(&(region->square), renderer, texfile, 0, 0, REGION_TILE_SIZE, REGION_TILE_SIZE);
	
	region->maxPopulation = 10000L;
	region->population = 0L;

	region->randDanger = rand()%1;
	region->temperature = baseTemp;
	region->humidity = baseHumid;
	region->terrain = baseTerr;
	region->growth = 0;
}

void Region_displayAt(Region* region, int x, int y)//determines where region is located on screen
{
	(region->square).bounds.x = x;
	(region->square).bounds.y = y;
}

unsigned Region_update(Region* region, int mx, int my, int clicked)//updates region when clicked upon
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

void Region_growPop(Region* region, Species* species)//function to grow population in a specific region
{
	double resourcei,dangeri,safetyi, rateG, rateD, grow/*, rate, decay, secondsG, secondsD*/;
	static long time = 0;
	static int counter=0;

	if(region->population > 0)//if region has a positive population. It will exbit the below growth/decay behavour 
	{
		time ++;
		resourcei = (0.5*(region->temperature)+2*(species->resourcefulness)+0.5*(region->humidity))/(double)200;//resource index
		dangeri = ((region->terrain)/(double)100) + (abs(region->temperature - 50)/(double)50) + region->randDanger - species->lifespan/30;//danger index
		safetyi = 12*(2*(species->strength)+2*(species->dexterity)+2*(species->tenacity))/(double)300;//safety index

		if(region->population >= region->maxPopulation || region->population < 0L)
			region->population = region->maxPopulation;
		else
		{
			rateG = (region->maxPopulation - region->population)/(double)region->maxPopulation*(resourcei+safetyi)/2+(rand()%3);//growth rate
			rateD = (2*dangeri-species->lifespan/30)*1.85*region->population/region->maxPopulation+(rand()%3);//decay rate
			grow = (rateG-rateD);//change in population
			if(counter==200){//loop to add evolution points
			
			species->evo_points += 1+rand()%3;
			counter-=200;	
			}
			if(grow>0){
				region->growth = 1;
			}
			else if(grow<0){
				region->growth = -1;
			}
			else{region->growth = 0;}
			//region->population *= 0.985;
			if((double)region->population+grow<0){region->population=0;}
			else{region->population += grow;}
		}
		counter++;
}
}

void Region_render(Region* region, SDL_Renderer* renderer)//SDL2 renders region
{
	Square_render(&(region->square), renderer);
}

void Region_destroy(Region* region)//region is now dead
{
	region->population = 0L;
	Square_destroy(&(region->square));
}
