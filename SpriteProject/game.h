#ifndef _GAME_H
#define _GAME_H

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#define APPTITLE "Trans_Sprite"

#define FULLSCREEN 0 //1 = fullscreen, 0 = windowed
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 448
#define TILE_SIZE 32

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

int Game_Init(HWND);
void Game_Run(HWND);
void Game_End(HWND);

struct SPRITE {
	int x, y;
	int width, height;
	int movex, movey;
	int curframe, lastframe;
	int animdelay, animcount;
	int direction;	// 2: down, 4: left, 6: right, 8: up 

	void move_right()
	{
		direction = 6;
		movex = 4;
		movey = 0;
	}

	void move_left()
	{
		direction = 4;
		movex = -4;
		movey = 0;
	}

	void move_up()
	{
		direction = 8;
		movex = 0;
		movey = -4;
	}

	void move_down()
	{
		direction = 2;
		movex = 0;
		movey = 4;
	}
};

struct MAP {
	int height;
	int width;
	int matrix[128][36];

	vector<int> solid_dungeon = { 5,8,9,10,16,17,18,19,20,22,32,34 };
	LPDIRECT3DSURFACE9 image[112];

	bool isSolid_Dungeon(int noColumn, int noRow)
	{
		for (int i = 0; i < solid_dungeon.size(); i++)
		{
			if (matrix[noRow][noColumn] == solid_dungeon[i])
			{
				return true;
			}
		}
		return false;
	}

	bool jason_collide_right(SPRITE s)
	{
		for (int i = (s.y + s.height / 2) / TILE_SIZE; i <= (s.y + s.height) / TILE_SIZE; i++)
		{
			if (isSolid_Dungeon((s.x + s.width + 4) / TILE_SIZE, i))
			{
				return true;
			}
		}
		return false;
	}
	bool jason_collide_left(SPRITE s)
	{
		for (int i = (s.y + s.height / 2) / TILE_SIZE; i <= (s.y + s.height) / TILE_SIZE; i++)
		{
			if (isSolid_Dungeon((s.x - 1) / TILE_SIZE, i))
			{
				return true;
			}
		}
		return false;
	}
	bool jason_collide_up(SPRITE s)
	{
		for (int j = s.x / TILE_SIZE; j <= (s.x + s.width) / TILE_SIZE; j++)
		{
			if (isSolid_Dungeon(j, (s.y - 1 + s.height / 2) / TILE_SIZE))
			{
				return true;
			}
		}
		return false;
	}
	bool jason_collide_down(SPRITE s)
	{
		for (int j = s.x / TILE_SIZE; j <= (s.x + s.width) / TILE_SIZE; j++)
		{
			if (isSolid_Dungeon(j, (s.y + 4 + s.height) / TILE_SIZE))
			{
				return true;
			}
		}
		return false;
	}
};

struct SOPHIA {
	int x, y;
	int width, height;
	int movex, movey;
	int animdelay, animcount;
	int direction;	// 2: down, 4: left, 6: right, 8: up 

	int gun_x, gun_y;
	int wheelleft_x, wheelleft_y;
	int wheelright_x, wheelright_y;
	int midwheel_x, midwheel_y;
	int body_x, body_y;

	int wheelcurframe, wheellastframe;

	void Update_wheel()
	{
		wheelleft_x = x, wheelleft_y = y + 16;
		wheelright_x = x + 32, wheelright_y = y + 16;
		midwheel_x = x + 16, midwheel_y = y + 16;
	}

	void Update_body()
	{
		if (direction == 6)
		{
			body_x = x, body_y = y;
			gun_x = x + 32, gun_y = y;
		}
		else if (direction == 4)
		{
			body_x = x + 16, body_y = y;
			gun_x = x, gun_y = y;
		}
	}

	void move_left()
	{
		direction = 4;
		movex = -4;
	}
	void move_right()
	{
		direction = 6;
		movex = 4;
	}
};

struct CAM {
	int x;
	int y;
	int movex;
	int movey;
};

#endif

