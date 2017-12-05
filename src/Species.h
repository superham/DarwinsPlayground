#ifndef GAME_SPECIES_H__
#define GAME_SPECIES_H__

typedef struct {

	unsigned strength;
	unsigned dexterity;
	unsigned resourcefulness;
	unsigned tenacity;
	unsigned lifespan; // generations
	unsigned fertility;
} Species;

void Species_init(Species*);
void Species_growRelative(Species*, int, int, int, int);

#endif /* GAME_SPECIES_H__ */
