#ifndef GAME_MENU_H__
#define GAME_MENU_H__

#if defined(__APPLE__)
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif
#include <SDL2/SDL.h>

#define MENU_OPEN 0
#define MENU_CLOSED 1
#define MENU_ANIMATING 2

typedef struct {

	SDL_Texture* texture;
	SDL_Rect clickable;
	SDL_Rect bounds;

	unsigned animating;
} Menu;

void Menu_init(Menu*, SDL_Renderer*, const char*, int, int, int, int);

unsigned Menu_checkMouse(Menu*, int, int, unsigned);
unsigned Menu_update(Menu*);

void Menu_render(Menu*, SDL_Renderer*);
void Menu_destroy(Menu*);

#endif /* GAME_MENU_H__ */
