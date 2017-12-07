#include "Textbox.h"

#include <stdio.h>
#include <string.h>

void Textbox_init(Textbox* textbox, char* text, int w, int h, int tw, int th)
{
	textbox->bounds.x = 0;
	textbox->bounds.y = 0;
	textbox->bounds.w = w;
	textbox->bounds.h = h;
	textbox->textWidth = tw;
	textbox->textHeight = th;

	textbox->textcolor = 0x00ffffff;
	textbox->boxcolor = 0x88000000;
	textbox->visible = 1;

	int len;
	len = strlen(text) > MAX_TEXT_SIZE ? MAX_TEXT_SIZE : strlen(text);

	memcpy(textbox->text, text, len);
	textbox->text[len] = 0;
}

void Textbox_setTextFromLong(Textbox* textbox, const char* msg, long value)
{
	char buffer[500];
	snprintf(buffer, 500, "%s%ld", msg, value);

	Textbox_setText(textbox, buffer, 1);
}

void Textbox_setText(Textbox* textbox, char* text, unsigned dynamic)
{
	int len;
	len = strlen(text) > MAX_TEXT_SIZE ? MAX_TEXT_SIZE : strlen(text);

	if(dynamic)
		textbox->textWidth = (int)(((double)(textbox->textWidth) * (double)strlen(text)) / (double)strlen(textbox->text));

	memcpy(textbox->text, text, len);
	textbox->text[len] = 0;
}

void Textbox_displayAt(Textbox* textbox, int x, int y)
{
	textbox->bounds.x = x;
	textbox->bounds.y = y;
}

static void getComponents(unsigned color, unsigned char* a, unsigned char* r, unsigned char* g, unsigned char* b)
{
	if(a != NULL)
		(*a) = (color >> 24) & 0xff;

	(*r) = (color >> 16) & 0xff;
	(*g) = (color >> 8) & 0xff;
	(*b) = color & 0xff;
}

void Textbox_render(Textbox* textbox, SDL_Renderer* renderer, TTF_Font* font)
{
	if(!(textbox->visible))
		return;

	unsigned char _r, _g, _b, _a;

	getComponents(textbox->boxcolor, &_a, &_r, &_g, &_b);

	SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);
	SDL_RenderFillRect(renderer, &(textbox->bounds));

	getComponents(textbox->textcolor, NULL, &_r, &_g, &_b);

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

void Textbox_renderRotatedText(Textbox* textbox, SDL_Renderer* renderer, TTF_Font* font, double angle)
{
	if(!(textbox->visible))
		return;

	unsigned char _r, _g, _b, _a;

	getComponents(textbox->boxcolor, &_a, &_r, &_g, &_b);

	SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);
	SDL_RenderFillRect(renderer, &(textbox->bounds));

	getComponents(textbox->textcolor, NULL, &_r, &_g, &_b);

	SDL_Color color = {.r=_r, .g=_g, .b=_b};
	SDL_Surface* surface = TTF_RenderText_Blended(font, textbox->text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect textBounds;
	textBounds.x = (textbox->bounds).x + ((textbox->bounds).w - textbox->textWidth) / 2;
	textBounds.y = (textbox->bounds).y + ((textbox->bounds).h - textbox->textHeight) / 2;
	textBounds.w = textbox->textWidth;
	textBounds.h = textbox->textHeight;

	SDL_RenderCopyEx(renderer, texture, NULL, &textBounds, angle, NULL, SDL_FLIP_NONE);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
