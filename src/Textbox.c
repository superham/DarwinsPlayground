#include "Textbox.h"

#include <stdio.h>
#include <string.h>

void Textbox_init(Textbox* textbox, char* text, int w, int h)
{
	textbox->bounds.x = 0;
	textbox->bounds.y = 0;
	textbox->bounds.w = w;
	textbox->bounds.h = h;

	textbox->textcolor = 0x00ffffff;
	textbox->boxcolor = 0x0;
	textbox->visible = 1;

	Textbox_setText(textbox, text);
}

void Textbox_setTextDims(Textbox* textbox, int tw, int th)
{
	textbox->textWidth = tw;
	textbox->textHeight = th;
}

void Textbox_setTextFromLong(Textbox* textbox, char* msg, long value)
{
	char buffer[500];
	snprintf(buffer, 5000, "%s%ld", msg, value);

	Textbox_setText(textbox, buffer);
}

void Textbox_setText(Textbox* textbox, char* text)
{
	int len;
	len = strlen(text) > MAX_TEXT_SIZE ? MAX_TEXT_SIZE : strlen(text);

	memcpy(textbox->text, text, len);
	textbox->text[len] = 0;
}

void Textbox_displayAt(Textbox* textbox, int x, int y)
{
	textbox->bounds.x = x;
	textbox->bounds.y = y;
}

static void getComponents(unsigned color, unsigned char* r, unsigned char* g, unsigned char* b)
{
	(*r) = (color >> 16) & 0xff;
	(*g) = (color >> 8) & 0xff;
	(*b) = color & 0xff;
}

void Textbox_render(Textbox* textbox, SDL_Renderer* renderer, TTF_Font* font)
{
	if(!(textbox->visible))
		return;
	
	unsigned char _r, _g, _b;

	getComponents(textbox->boxcolor, &_r, &_g, &_b);

	SDL_SetRenderDrawColor(renderer, _r, _g, _b, 0xff);
	SDL_RenderFillRect(renderer, &(textbox->bounds));

	getComponents(textbox->textcolor, &_r, &_g, &_b);

	SDL_Color color = {.r=_r, .g=_g, .b=_b};
	SDL_Surface* surface = TTF_RenderText_Blended(font, textbox->text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect textBounds;
	textBounds.x = (textbox->bounds).x + ((textbox->bounds).w - textbox->textWidth) / 2;
	textBounds.y = (textbox->bounds).y + ((textbox->bounds).h - textbox->textHeight) / 2;
	textBounds.w = textbox->textWidth;
	textBounds.h = textbox->textHeight;

	SDL_RenderCopy(renderer, texture, NULL, &textBounds);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
