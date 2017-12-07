#include "Menu.h"
#include "Square.h"

#include <stdlib.h>
#include <stdio.h>

#define MENU_ANIMATE_DX 20

static const char* titles[4] = {"Strength", "Dexterity", "Tenacity", "Resourcefulness"};

void Menu_init(Menu* menu, SDL_Renderer* renderer, const char* texfile, int cw, int ch, int iw, int ih)//initialize evolve menu
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

	Evolve_init(&(menu->buttons[0][0]), renderer, "resources/strbutton.png", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Evolve_init(&(menu->buttons[1][0]), renderer, "resources/dexbutton.png", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Evolve_init(&(menu->buttons[2][0]), renderer, "resources/tenbutton.png", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Evolve_init(&(menu->buttons[3][0]), renderer, "resources/resbutton.png", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
//initialized values of evolve traits, in order of base attributes then regional modifiers/misc bonuses
	Evolve_init(&(menu->buttons[0][1]), renderer, "resources/increased_size.png", 15, -5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10);
	Evolve_init(&(menu->buttons[0][2]), renderer, "resources/tough_claws.png", 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10);
	Evolve_init(&(menu->buttons[0][3]), renderer, "resources/iron_grip.png", 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 10);
	Evolve_init(&(menu->buttons[0][4]), renderer, "resources/dumb_muscle.png", 25, -10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20);
	Evolve_init(&(menu->buttons[0][5]), renderer, "resources/bone_spikes.png", 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20);
	Evolve_init(&(menu->buttons[0][6]), renderer, "resources/strong_jaw.png", 10, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 20);

	Evolve_init(&(menu->buttons[1][1]), renderer, "resources/small_frame.png", -5, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10);
	Evolve_init(&(menu->buttons[1][2]), renderer, "resources/tail.png", 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10);
	Evolve_init(&(menu->buttons[1][3]), renderer, "resources/natural_camoflauge.png", 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 10);
	Evolve_init(&(menu->buttons[1][4]), renderer, "resources/prehensile_tail.png", 0, 10, 0, 0, 0, 0, 0, 0, 5, 0, 0, 20);
	Evolve_init(&(menu->buttons[1][5]), renderer, "resources/powerful_hind_legs.png", 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20);
	Evolve_init(&(menu->buttons[1][6]), renderer, "resources/opposable_thumbs.png", 0, 10, 0, 5, 0, 0, 0, 0, 0, 0, 0, 20);

	Evolve_init(&(menu->buttons[2][1]), renderer, "resources/thick_fur.png", 0, 0, 10, 0, -5, 5, 0, 0, 0, 0, 0, 10);
	Evolve_init(&(menu->buttons[2][2]), renderer, "resources/hard_shell.png", 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 10);
	Evolve_init(&(menu->buttons[2][3]), renderer, "resources/water_reserves.png", 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 0, 10);
	Evolve_init(&(menu->buttons[2][4]), renderer, "resources/fertility.png", 0, 0, 10, 0, 0, 0, 0, 0, 0, 2, 0, 20);
	Evolve_init(&(menu->buttons[2][5]), renderer, "resources/exoskeleton.png", 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 20);
	Evolve_init(&(menu->buttons[2][6]), renderer, "resources/longevity.png", 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 10, 20);

	Evolve_init(&(menu->buttons[3][1]), renderer, "resources/wolf_pack_tactics.png", 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 10);
	Evolve_init(&(menu->buttons[3][2]), renderer, "resources/night_vision.png", 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 10);
	Evolve_init(&(menu->buttons[3][3]), renderer, "resources/improved_foraging.png", 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 10);
	Evolve_init(&(menu->buttons[3][4]), renderer, "resources/insomniac.png", -10, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 20);
	Evolve_init(&(menu->buttons[3][5]), renderer, "resources/olfactory_acuity.png", 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 20);
	Evolve_init(&(menu->buttons[3][6]), renderer, "resources/extra_stomach.png", 0, -10, 0, 25, 0, 0, 0, 0, 0, 0, 0, 20);

	Evolve_setDescription(&(menu->buttons[0][1]), "Increased Size");
	Evolve_setDescription(&(menu->buttons[0][2]), " Tough Claws  ");
	Evolve_setDescription(&(menu->buttons[0][3]), "  Iron Grip   ");
	Evolve_setDescription(&(menu->buttons[0][4]), " Dumb Muscle  ");
	Evolve_setDescription(&(menu->buttons[0][5]), " Bone Spikes  ");
	Evolve_setDescription(&(menu->buttons[0][6]), "  Strong Jaw  ");

	Evolve_setDescription(&(menu->buttons[1][1]), "   Small Frame    ");
	Evolve_setDescription(&(menu->buttons[1][2]), "      Tail      ");
	Evolve_setDescription(&(menu->buttons[1][3]), "    Camouflage    ");
	Evolve_setDescription(&(menu->buttons[1][4]), " Prehensile Tail ");
	Evolve_setDescription(&(menu->buttons[1][5]), "Powerful Hind Legs");
	Evolve_setDescription(&(menu->buttons[1][6]), "Opposable Thumbs");

	Evolve_setDescription(&(menu->buttons[2][1]), "  Thick Fur   ");
	Evolve_setDescription(&(menu->buttons[2][2]), "  Hard Shell  ");
	Evolve_setDescription(&(menu->buttons[2][3]), "Water Reserves");
	Evolve_setDescription(&(menu->buttons[2][4]), "  Fertility   ");
	Evolve_setDescription(&(menu->buttons[2][5]), " Exoskeleton  ");
	Evolve_setDescription(&(menu->buttons[2][6]), "  Longevity   ");

	Evolve_setDescription(&(menu->buttons[3][1]), "Pack Mentality");
	Evolve_setDescription(&(menu->buttons[3][2]), " Night Vision ");
	Evolve_setDescription(&(menu->buttons[3][3]), "   Foraging   ");
	Evolve_setDescription(&(menu->buttons[3][4]), "  Nocturnal   ");
	Evolve_setDescription(&(menu->buttons[3][5]), "Olfactory Acuity");
	Evolve_setDescription(&(menu->buttons[3][6]), "Extra Stomach");

	Evolve_moveTo(&(menu->buttons[0][0]), 150, 75);
	Evolve_moveTo(&(menu->buttons[1][0]), 150, 200);
	Evolve_moveTo(&(menu->buttons[2][0]), 150, 325);
	Evolve_moveTo(&(menu->buttons[3][0]), 150, 450);

	int i;
	for(i = 0; i < NUM_EVOLVE_TREES; i ++)
	{
		Evolve_hideDescription(&(menu->buttons[i][0]));

		Evolve_moveTo(&(menu->buttons[i][1]), 350, 137);
		Evolve_moveTo(&(menu->buttons[i][2]), 350, 262);
		Evolve_moveTo(&(menu->buttons[i][3]), 350, 387);
		Evolve_moveTo(&(menu->buttons[i][4]), 525, 137);
		Evolve_moveTo(&(menu->buttons[i][5]), 525, 262);
		Evolve_moveTo(&(menu->buttons[i][6]), 525, 387);
	}

	Textbox_init(&(menu->title), "Strength", 200, 44, 90, 30);
	Textbox_displayAt(&(menu->title), 375, 20);
	
	Textbox_init(&(menu->points), "0", 150, 40, 30, 30);
	Textbox_displayAt(&(menu->points), 710, 280);

	menu->title.boxcolor = EVOLVE_LABEL_COLOR;
	menu->title.visible = 0;
	
	menu->points.boxcolor = 0x0;

	menu->state = MENU_CLOSED;
	menu->animating = 0;
	menu->selected = -1;
}

unsigned Menu_checkMouse(Menu* menu, Species* species, int mx, int my, unsigned clicked)//checks where mouse is/if it is clicking
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

	if(menu->state == MENU_OPEN)
	{
		int i;
		for(i = 0; i < NUM_EVOLVE_TREES; i ++)
		{
			if(Square_intersectsPoint(&(menu->buttons[i][0].square), mx, my) && clicked)
			{
				Textbox_setText(&(menu->title), (char*)(titles[i]), 1);
				menu->title.visible = 1;
				menu->selected = i;

				break;
			}
		}

		if(menu->selected != -1)
		{
			for(i = 1; i <= NUM_EVOLVE_SUBS; i ++)
			{
				if(Square_intersectsPoint(&(menu->buttons[menu->selected][i].square), mx, my) && clicked)
				{
					if(!(menu->buttons[menu->selected][i].applied) && species->evo_points >= (menu->buttons[menu->selected][i]).evo_cost)//checks if you have enough points to evolve
						Evolve_trait(&(menu->buttons[menu->selected][i]), species);
				}
			}
		}
	}

	return 0;
}

unsigned Menu_update(Menu* menu)
{
	if(menu->animating && menu->bounds.x > 0)
	{
		menu->bounds.x -= MENU_ANIMATE_DX;
		menu->points.bounds.x -= MENU_ANIMATE_DX;

		if(menu->bounds.x < 0)
			menu->bounds.x = 0;
		
		if(menu->points.bounds.x < (menu->points.bounds.w / 2))
			menu->points.bounds.x = (menu->points.bounds.w / 2);
	}
	else if(!(menu->animating) && menu->bounds.x < (menu->bounds.w - menu->clickable.w))
	{
		menu->bounds.x += MENU_ANIMATE_DX;
		menu->points.bounds.x += MENU_ANIMATE_DX;

		if(menu->bounds.x > (menu->bounds.w - menu->clickable.w))
			menu->bounds.x = (menu->bounds.w - menu->clickable.w);
		
		if(menu->points.bounds.x > (menu->bounds.w - menu->clickable.w) + (menu->points.bounds.w / 2))
			menu->points.bounds.x = (menu->bounds.w - menu->clickable.w) + (menu->points.bounds.w / 2);
	}
	menu->clickable.x = menu->bounds.x;

	if(menu->bounds.x <= 0)
		return (menu->state = MENU_OPEN);

	else if(menu->bounds.x >= (menu->bounds.w - menu->clickable.w))
	{
		menu->selected = -1;
		menu->title.visible = 0;

		return (menu->state = MENU_CLOSED);
	}

	else return (menu->state = MENU_ANIMATING);
}

void Menu_render(Menu* menu, SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_RenderCopy(renderer, menu->texture, NULL, &(menu->bounds));

	if(menu->state == MENU_OPEN)
	{
		unsigned char alpha;

		int i;
		for(i = 0; i < NUM_EVOLVE_TREES; i ++)
		{
			alpha = (menu->selected == i) ? 0x83 : 0x44;

			SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, alpha);
			SDL_RenderFillRect(renderer, &(menu->buttons[i][0].square.bounds));

			Evolve_render(&(menu->buttons[i][0]), renderer, font);
		}

		if(menu->selected != -1)
		{
			for(i = 1; i <= NUM_EVOLVE_SUBS; i ++)
			{
				Evolve_render(&(menu->buttons[menu->selected][i]), renderer, font);

				if(menu->buttons[menu->selected][i].applied)
				{
					SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 0xAA);
					SDL_RenderFillRect(renderer, &(menu->buttons[menu->selected][i].square.bounds));
				}
			}
		}
		Textbox_render(&(menu->title), renderer, font);
	}
	//Textbox_renderRotatedText(&(menu->points), renderer, font, 90.0);
}

void Menu_destroy(Menu* menu)
{
	int i, j;
	for(i = 0; i < NUM_EVOLVE_TREES; i ++)
		for(j = 0; j <= NUM_EVOLVE_SUBS; j ++)
			Evolve_destroy(&(menu->buttons[i][j]));

	SDL_DestroyTexture(menu->texture);
}
