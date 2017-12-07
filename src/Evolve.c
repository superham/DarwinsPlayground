#include "Evolve.h"

//Evolution initilaztion function
void Evolve_init(Evolve* evolve, SDL_Renderer* renderer, const char* texfile, int dstr, int ddex, int dten, int dres, int dhot, int dcold, int darid, int dmount, int dforest, int dfertility, int dlifespan, int cost)
{
	Square_create(&(evolve->square), renderer, texfile, 0, 0, EVOLVE_TILE_SIZE, EVOLVE_TILE_SIZE);
	Textbox_init(&(evolve->textbox), "", EVOLVE_TILE_SIZE + 30, EVOLVE_TILE_SIZE / 2, EVOLVE_TILE_SIZE + 16, (EVOLVE_TILE_SIZE / 2) - 14);
	evolve->textbox.boxcolor = EVOLVE_LABEL_COLOR;

	evolve->d_str = dstr;
	evolve->d_dex = ddex;
	evolve->d_ten = dten;
	evolve->d_res = dres;
	evolve->d_hot = dhot;

	evolve->d_cold = dcold;
	evolve->d_arid = darid;
	evolve->d_mount = dmount;
	evolve->d_forest = dforest;
	evolve->d_fertility = dfertility;
	evolve->d_lifespan = dlifespan;

	evolve->applied = 0;
	evolve->evo_cost = cost;
}


void Evolve_trait(Evolve* evolve, Species* species)//applies bonuses from traits to species
{
	Species_growRelative(species, evolve->d_str, evolve->d_dex, evolve->d_ten, evolve->d_res);

	species->d_hot += evolve->d_hot;
	species->d_cold += evolve->d_cold;
	species->d_arid += evolve->d_arid;
	species->d_mount += evolve->d_mount;
	species->d_forest += evolve->d_forest;
	species->fertility += evolve->d_fertility;
	species->lifespan+= evolve->d_lifespan;
	
	species->evo_points -= evolve->evo_cost;

	evolve->applied = 1;
}

void Evolve_moveTo(Evolve* evolve, int x, int y)//moves physical evolution location
{
	evolve->square.bounds.x = x;
	evolve->square.bounds.y = y;

	evolve->textbox.bounds.x = x - 15;
	evolve->textbox.bounds.y = y - evolve->textbox.bounds.h;
}

void Evolve_hideDescription(Evolve* evolve)//hides evolution popup
{
	evolve->textbox.visible = 0;
}

void Evolve_setDescription(Evolve* evolve, const char* title)//sets evolution desc.
{
	Textbox_setText(&(evolve->textbox), (char*)title, 0);
}

void Evolve_render(Evolve* evolve, SDL_Renderer* renderer, TTF_Font* font)//renders evolution text
{
	Textbox_render(&(evolve->textbox), renderer, font);
	SDL_RenderCopy(renderer, evolve->square.texture, NULL, &(evolve->square.bounds));
}

void Evolve_destroy(Evolve* evolve)//removes evolve txt
{
	Square_destroy(&(evolve->square));
}
