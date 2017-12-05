#ifndef GAME_SQUARE_H__
#define GAME_SQUARE_H__

#if defined(__APPLE__)
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

#include <SDL2/SDL.h>

#define SQUARE_SIZE 50

typedef struct
{
	SDL_Texture* texture;
	SDL_Rect bounds;

	unsigned color;
	int tw;
	int th;
} Square;

void Square_create(Square*, SDL_Renderer*, const char*, int, int, int, int);
void Square_render(Square*, SDL_Renderer*);
unsigned Square_intersectsPoint(Square*, int, int);

void Square_destroy(Square*);

#endif /* GAME_SQUARE_H__ */
