#ifndef GAME_MENU_H__
#define GAME_MENU_H__

#include "Evolve.h"
#include "Species.h"

#if defined(__APPLE__)
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif
#include <SDL2/SDL.h>

#define MENU_OPEN 1
#define MENU_CLOSED 0
#define MENU_ANIMATING 2

#define NUM_EVOLVE_TREES 4
#define NUM_EVOLVE_SUBS 6

typedef struct {

	SDL_Texture* texture;
	SDL_Rect clickable;
	SDL_Rect bounds;

	Evolve buttons[NUM_EVOLVE_TREES][NUM_EVOLVE_SUBS + 1];
	
	Textbox points;
	Textbox title;

	unsigned animating;
	unsigned selected;
	unsigned state;
} Menu;

void Menu_init(Menu*, SDL_Renderer*, const char*, int, int, int, int);

unsigned Menu_checkMouse(Menu*, Species*, int, int, unsigned);
unsigned Menu_update(Menu*);

void Menu_render(Menu*, SDL_Renderer*, TTF_Font*);
void Menu_destroy(Menu*);

#endif /* GAME_MENU_H__ */
