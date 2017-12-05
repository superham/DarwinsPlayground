#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Region.h"
#include "Textbox.h"

#define WINDOW_TITLE "Darwin's Playground"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define BOARD_SIZE 6

Region board[BOARD_SIZE * BOARD_SIZE];
Species mainSpecies;
Textbox mainInfo;

Textbox regionInfo;

SDL_Texture* background;
TTF_Font* fontArial;

SDL_Renderer* mainRenderer;
SDL_Window* mainWindow;

void updateAll(unsigned*);
void renderAll(void);
int initAll(void);

void createBoard(Region _[], int);
void createBackground(void);

void cleanup(void);

int main(int argc, char* argv[])
{
	if(initAll() != 0)
		return 1;

	Species_init(&mainSpecies);

	Textbox_init(&mainInfo, "Population: 0", WINDOW_WIDTH - 40, 60);
	Textbox_setTextDims(&mainInfo, 150, 30);
	Textbox_displayAt(&mainInfo, 20, 5);

	Textbox_init(&regionInfo, "Pop: 0", 90, 50);
	Textbox_setTextDims(&regionInfo, 40, 16);
	regionInfo.visible = 0;

#define NUM_REGIONS 5

	Region baseRegions[NUM_REGIONS];
	Region_init(&(baseRegions[0]), mainRenderer, "resources/forestBroadleaf00.png", 65, 40, 50);
	Region_init(&(baseRegions[1]), mainRenderer, "resources/mountain00.png", 20, 50, 90);
	Region_init(&(baseRegions[2]), mainRenderer, "resources/plains00.png", 80, 70, 10);
	Region_init(&(baseRegions[3]), mainRenderer, "resources/desertDunes00.png", 100, 10, 10);
	Region_init(&(baseRegions[4]), mainRenderer, "resources/marsh00.png", 55, 75, 100);

	createBoard(baseRegions, NUM_REGIONS);
	createBackground();

	unsigned running;
	running = 1;

	while(running)
	{
		updateAll(&running);
		renderAll();
	}

	int i;
	for(i = 0; i < NUM_REGIONS; i ++)
		Region_destroy(&(baseRegions[i]));

#undef NUM_REGIONS

	cleanup();
	return 0;
}

int initAll()
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error: Failed to init SDL2!\n");
		return -1;
	}

	if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		fprintf(stderr, "Error: Failed to init SDL2_image!\n");
		cleanup();

		return -1;
	}

	if(TTF_Init() != 0)
	{
		fprintf(stderr, "Error: Failed to init SDL2_ttf!\n");
		cleanup();

		return -1;
	}

	mainWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
								WINDOW_HEIGHT, 0);
	if(mainWindow == NULL)
	{
		fprintf(stderr, "Error: Failed to create main window!\n");
		cleanup();

		return -1;
	}
	mainRenderer = SDL_CreateRenderer(mainWindow, 0,
									SDL_RENDERER_PRESENTVSYNC |
									SDL_RENDERER_ACCELERATED);
	if(mainRenderer == NULL)
	{
		fprintf(stderr, "Error: Failed to create main rendering context!");
		cleanup();

		return -1;
	}
	SDL_SetRenderDrawBlendMode(mainRenderer, SDL_BLENDMODE_BLEND);
	
	fontArial = TTF_OpenFont("resources/arial.ttf", 240);

	if(fontArial == NULL)
	{
		fprintf(stderr, "Error: Failed to load main font file(s)!\n");
		cleanup();

		return -1;
	}
	return 0;
}

void cleanup()
{
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyTexture(background);

	TTF_CloseFont(fontArial);
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void createBackground()
{
	SDL_Surface* image = IMG_Load("resources/background.png");
	if(image == NULL)
	{
		fprintf(stderr, "Error: Failed to load image 'resources/background.png'!\n");
		exit(1);
	}
	background = SDL_CreateTextureFromSurface(mainRenderer, image);

	SDL_SetTextureAlphaMod(background, 170);
	SDL_FreeSurface(image);
}

void createBoard(Region regionTypes[], int numTypes)
{
	srand(time(NULL));

	int xoffset, yoffset;
	xoffset = (WINDOW_WIDTH - (REGION_TILE_SIZE * BOARD_SIZE)) / 2;
	yoffset = (WINDOW_HEIGHT - (REGION_TILE_SIZE * BOARD_SIZE)) / 2;

	int i, j;
	for(i = 0; i < BOARD_SIZE; i ++)
	{
		for(j = 0; j < BOARD_SIZE; j ++)
		{
			int type;

			type = rand() % numTypes;
			board[i + j * BOARD_SIZE] = regionTypes[type];

			Region_displayAt(&(board[i + j * BOARD_SIZE]), i * REGION_TILE_SIZE + xoffset, j *  REGION_TILE_SIZE + yoffset);
		}
	}
}

static void consolidateRegion(int index)
{
	int adjacents[8] = {
			index - 1,
			index + 1,
			index + BOARD_SIZE,
			index - BOARD_SIZE,
			index + BOARD_SIZE + 1,
			index + BOARD_SIZE - 1,
			index - BOARD_SIZE + 1,
			index - BOARD_SIZE - 1
	};

	int i;
	for(i = 0; i < 8; i ++)
	{
		if(adjacents[i] < 0 || adjacents[i] >= BOARD_SIZE * BOARD_SIZE)
			continue;

		if(board[adjacents[i]].population == 0)
		{
			long newPop;
			newPop = (long)((double)board[index].population * 0.70);

			board[adjacents[i]].population = board[index].population - newPop;
			board[index].population = newPop;

			break;
		}
	}
}

void updateAll(unsigned* running)
{
	static unsigned gameStarted = 0;
	static unsigned frames = 0;
	static int hoverIndex = -1;

	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
			*running = 0;

		else if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			if(!(gameStarted && e.button.button == SDL_BUTTON_LEFT))
			{
				int i;
				for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i ++)
				{
					unsigned state;
					state = Region_update(&(board[i]), e.motion.x, e.motion.y, e.button.button == SDL_BUTTON_LEFT);

					if(state == CLICK_ON_REGION)
						gameStarted = 1;
				}
			}
		}
		else if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP)
		{
			int newHoverIndex;
			newHoverIndex = -1;

			int i;
			for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i ++)
			{
				unsigned state;
				state = Region_update(&(board[i]), e.motion.x, e.motion.y, 0);

				if(state == HOVER_ON_REGION)
				{
					if(hoverIndex != i)
						Textbox_setTextFromLong(&regionInfo, "Pop: ", board[i].population);

					newHoverIndex = i;
				}
			}
			hoverIndex = newHoverIndex;
		}
	}
	
	int i;
	for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i ++)
	{
		if(hoverIndex == i)
			continue;

		Region_update(&(board[i]), 0, 0, 0);
	}

	if(hoverIndex != -1)
	{
		Textbox_displayAt(&regionInfo, board[hoverIndex].square.bounds.x, board[hoverIndex].square.bounds.y - regionInfo.bounds.h);
		regionInfo.visible = 1;
	}
	else regionInfo.visible = 0;

	unsigned long netPopulation;
	netPopulation = 0L;

	for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i ++)
	{
		if(board[i].population >= (board[i].maxPopulation / 2))
			consolidateRegion(i);

		Region_growPop(&(board[i]), &mainSpecies);

		netPopulation += board[i].population;
	}

	if(frames == 60)
	{
		if(hoverIndex != -1)
			Textbox_setTextFromLong(&regionInfo, "Pop: ", board[hoverIndex].population);

		Textbox_setTextFromLong(&mainInfo, "Population: ", netPopulation);
		frames = 0;
	}
	else frames ++;
}

void renderAll()
{
	SDL_SetRenderDrawColor(mainRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(mainRenderer);

	SDL_Rect dest = {.x=0, .y=0, .w=WINDOW_WIDTH, .h=WINDOW_HEIGHT};
	SDL_RenderCopy(mainRenderer, background, NULL, &dest);

	int i;
	for(i = 0; i < BOARD_SIZE * BOARD_SIZE; i ++)
	{
		Region_render(&(board[i]), mainRenderer);

		if(board[i].population)
			printf("Tile %d: %ld\n", i, board[i].population);
	}

	Textbox_render(&mainInfo, mainRenderer, fontArial);
	Textbox_render(&regionInfo, mainRenderer, fontArial);

	SDL_RenderPresent(mainRenderer);
}
