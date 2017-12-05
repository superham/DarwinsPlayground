#include "Square.h"

#include <stdio.h>
#include <stdlib.h>

void Square_create(Square* square, SDL_Renderer* renderer, const char* texfile, int x, int y, int w, int h)
{
	SDL_Surface* image = IMG_Load(texfile);
	if(image == NULL)
	{
		fprintf(stderr, "Error: Failed to load image '%s'!\n", texfile);
		exit(1);
	}
	square->texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	square->bounds.x = x;
	square->bounds.y = y;
	square->bounds.w = w;
	square->bounds.h = h;
	square->color = 0x00ffffff;

	int _sw, _sh;
	float aspect;

	SDL_QueryTexture(square->texture, NULL, NULL, &_sw, &_sh);
	aspect = (float)_sh / (float)_sw;

	square->th = (int)((float)h * aspect);
	square->tw = w;
}

void Square_render(Square* square, SDL_Renderer* renderer)
{
	unsigned char r, g, b;
	r = (square->color >> 16) & 0xff;
	g = (square->color >> 8) & 0xff;
	b = (square->color) & 0xff;

	SDL_Rect dest = {.x=(square->bounds).x, .y=(square->bounds).y - (square->th - (square->bounds).h), .w=square->tw, .h=square->th};

	SDL_SetTextureColorMod(square->texture, r, g, b);
	SDL_RenderCopy(renderer, square->texture, NULL, &dest);
}

unsigned Square_intersectsPoint(Square* square, int x, int y)
{
	int tw, th, rw, rh;

	tw = square->bounds.w;
	th = square->bounds.h;
	rw = x + 1;
	rh = y + 1;

	if(tw <= 0 || th <= 0)
		return 0;

	tw += (square->bounds.x);
	th += (square->bounds.y);

	return ((rw > (square->bounds.x)) &&
		(rh > (square->bounds.y)) &&
		(tw < (square->bounds.x) || tw > x) &&
		(th < (square->bounds.y) || th > y));
}

void Square_destroy(Square* square)
{
	SDL_DestroyTexture(square->texture);
}
