#pragma once

#include "cTexture.h"

#define SCENE_Xo		0//(2*TILE_SIZE)
#define SCENE_Yo		0//TILE_SIZE
#define SCENE_WIDTH		10 //640 width / 64 tamano 
#define SCENE_HEIGHT	8

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		64
#define BLOCK_SIZE		64

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	void Draw(int tex_id);
	void DrawBackground(int tex_id);
	int *GetMap();
	int BACK_HEIGHT, BACK_WIDTH_DRAW;
	int tilesFila;

private:
	int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	int id_DL;								//actual level display list
};
