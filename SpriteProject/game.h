#ifndef _GAME_H
#define _GAME_H

#define APPTITLE "Trans_Sprite"

#define FULLSCREEN 0 //1 = fullscreen, 0 = windowed
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 448

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
};

#endif

