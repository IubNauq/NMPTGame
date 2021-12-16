#ifndef _GAME_H
#define _GAME_H

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>

#include "sophia.h"
#include "sprite.h"
#include "map.h"

using namespace std;

#define APPTITLE "Blaster Master"

#define FULLSCREEN 0 //1 = fullscreen, 0 = windowed
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 448
#define TILE_SIZE 32

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

int Game_Init(HWND);
void Game_Run(HWND);
void Game_End(HWND);

class BULLET
{
public:
	int x, y;
	int width, height;
	int movex, movey;
	int direction;	// 0: left, 1: right, 2:up, 3: down

	bool up_down;	// used for jason bullet
};

class CAM {
public:
	int x;
	int y;
};

#endif

