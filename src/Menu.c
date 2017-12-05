#include "Menu.h"
#include "Square.h"

#include <stdlib.h>
#include <stdio.h>

#define MENU_ANIMATE_DX 20

void Menu_init(Menu* menu, SDL_Renderer* renderer, const char* texfile, int cw, int ch, int iw, int ih)
{
	SDL_Surface* image = IMG_Load(texfile);
	if(image == NULL)
	{
		fprintf(stderr, "Error: Failed to load image '%s'!\n", texfile);
		exit(1);
	}
	menu->texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	menu->clickable.x = iw;
	menu->clickable.y = (ih / 2) - (ch / 2);
	menu->clickable.w = cw;
	menu->clickable.h = ch;

	menu->bounds.w = iw;
	menu->bounds.h = ih;
	menu->bounds.x = iw - cw;
	menu->bounds.y = 0;

	menu->animating = 0;
}

unsigned Menu_checkMouse(Menu* menu, int mx, int my, unsigned clicked)
{
	static unsigned canClick = 1;

	Square menuSquare;
	menuSquare.texture = NULL;
	menuSquare.bounds.x = (menu->clickable).x;
	menuSquare.bounds.y = (menu->clickable).y;
	menuSquare.bounds.w = (menu->clickable).w;
	menuSquare.bounds.h = (menu->clickable).h;

	if(Square_intersectsPoint(&menuSquare, mx, my) && clicked && canClick)
	{
		menu->animating = !(menu->animating);
		canClick = 0;

		return 1;
	}
	else if(!clicked)
		canClick = 1;

	return 0;
}

unsigned Menu_update(Menu* menu)
{
	if(menu->animating && menu->bounds.x > 0)
	{
		menu->bounds.x -= MENU_ANIMATE_DX;

		if(menu->bounds.x < 0)
			menu->bounds.x = 0;
	}
	else if(!(menu->animating) && menu->bounds.x < (menu->bounds.w - menu->clickable.w))
	{
		menu->bounds.x += MENU_ANIMATE_DX;

		if(menu->bounds.x > (menu->bounds.w - menu->clickable.w))
			menu->bounds.x = (menu->bounds.w - menu->clickable.w);
	}
	menu->clickable.x = menu->bounds.x;

	if(menu->bounds.x <= 0)
		return MENU_CLOSED;

	else if(menu->bounds.x >= (menu->bounds.w - menu->clickable.w))
		return MENU_OPEN;

	else return MENU_ANIMATING;
}

void Menu_render(Menu* menu, SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, menu->texture, NULL, &(menu->bounds));
}

void Menu_destroy(Menu* menu)
{
	SDL_DestroyTexture(menu->texture);
}
