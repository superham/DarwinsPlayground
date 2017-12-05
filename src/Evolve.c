#include "Evolve.h"
void Evolve_init(Evolve* evolve, SDL_Renderer* renderer, const char* texfile, int dstr, int ddex, int dten, int dres, int dhot, int dcold, int darid, int dmount, int dforest)
{
	Square_create(&(evolve->square), renderer, texfile, 0, 0, EVOLVE_TILE_SIZE, EVOLVE_TILE_SIZE);
	evolve->d_str = dstr;
	evolve->d_dex = ddex;
	evolve->d_ten = dten;
	evolve->d_res = dres;
	evolve->d_hot = dhot;
	evolve->d_cold = dcold;
	evolve->d_arid = darid;
	evolve->d_mount = dmount;
	evolve->d_forest = dforest;
}
void Evolve_trait(Evolve* evolve, Species* species)
{
	Species_growRelative(species, evolve->d_str, evolve->d_dex, evolve->d_ten, evolve->d_res);
	species->d_hot += evolve->d_hot;
	species->d_cold += evolve->d_cold;
	species->d_arid += evolve->d_arid;
	species->d_mount += evolve->d_mount;
	species->d_forest += evolve->d_forest;
	
	
}
