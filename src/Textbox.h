#ifndef GAME_TEXTBOX_H__
#define GAME_TEXTBOX_H__

#if defined(__APPLE__)
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

#define MAX_TEXT_SIZE 500

typedef struct {

	SDL_Rect bounds;
	char text[MAX_TEXT_SIZE];

	int textWidth;
	int textHeight;

	unsigned textcolor;
	unsigned boxcolor;
	unsigned visible;
} Textbox;

void Textbox_init(Textbox*, char*, int, int, int, int);
void Textbox_displayAt(Textbox*, int, int);

void Textbox_setTextFromLong(Textbox*, const char*, long);
void Textbox_setText(Textbox*, char*, unsigned);

void Textbox_render(Textbox*, SDL_Renderer*, TTF_Font*);
void Textbox_renderRotatedText(Textbox*, SDL_Renderer*, TTF_Font*, double);

#endif /* GAME_TEXTBOX_H__ */
