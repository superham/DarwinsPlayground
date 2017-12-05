#ifndef GAME_EVOLVE_H_
#define GAME_EVOLVE_H_
#define EVOLVE_TILE_SIZE 60
#include "Square.h"
#include "Species.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
typedef struct {
	Square square;
	//attribute modifiers
	int d_str;
	int d_dex;
	int d_ten;
	int d_res;
	
	//independent modifiers 
	int d_cold;
	int d_hot;
	int d_arid;
	int d_mount;
	int d_forest;

}Evolve;
void Evolve_init(Evolve* evolve, SDL_Renderer* renderer, const char* texfile, int dstr, int ddex, int dten, int dres, int dhot, int dcold, int darid, int dmount, int dforest);
void Evolve_trait(Evolve *evolve, Species *species);
#endif /*GAME_EVOLVE_H_*/