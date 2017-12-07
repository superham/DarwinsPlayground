#ifndef GAME_SPECIES_H__
#define GAME_SPECIES_H__

typedef struct {

	unsigned strength;
	unsigned dexterity;
	unsigned resourcefulness;
	unsigned tenacity;
	unsigned lifespan;
	unsigned fertility;

	int d_hot;
	int d_cold;
	int d_arid;
	int d_mount;
	int d_forest;
	int evo_points;
} Species;

void Species_init(Species*);
void Species_growRelative(Species*, int, int, int, int);

#endif /* GAME_SPECIES_H__ */
