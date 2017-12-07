#ifndef GAME_EVOLVE_H_
#define GAME_EVOLVE_H_

#include <SDL2/SDL.h>

#if defined(__APPLE__)
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Square.h"
#include "Species.h"
#include "Textbox.h"

#define EVOLVE_TILE_SIZE 75
#define EVOLVE_LABEL_COLOR 0x73555555

typedef struct {//evolution structure

	Textbox textbox;
	Square square;

	unsigned applied;

	int d_str;
	int d_dex;
	int d_ten;
	int d_res;

	int d_cold;
	int d_hot;
	int d_arid;
	int d_mount;
	int d_forest;
	int d_fertility;
	int d_lifespan;
	int evo_cost;
} Evolve;

void Evolve_init(Evolve*, SDL_Renderer*, const char*, int, int, int, int, int, int, int, int, int, int, int, int);
void Evolve_trait(Evolve*, Species*);

void Evolve_moveTo(Evolve*, int, int);

void Evolve_hideDescription(Evolve*);
void Evolve_setDescription(Evolve*, const char*);

void Evolve_render(Evolve*, SDL_Renderer*, TTF_Font*);
void Evolve_destroy(Evolve*);

#endif /*GAME_EVOLVE_H_*/
