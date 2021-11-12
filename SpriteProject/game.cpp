#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <string>

#include "game.h"
#include "dxgraphics.h"

LPDIRECT3DTEXTURE9 player_image_right[3];
LPDIRECT3DTEXTURE9 player_image_left[3];
LPDIRECT3DTEXTURE9 player_image_up[3];
LPDIRECT3DTEXTURE9 player_image_down[3];
SPRITE player_auto;
SPRITE player_control;

LPDIRECT3DSURFACE9 background;
LPD3DXSPRITE sprite_handler;
HRESULT result;

long start = GetTickCount();

int Game_Init(HWND hwnd)
{
	srand(time(NULL));

	char s[100];

	/*if (!Init_Keyboard(hwnd))
	{
		MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}*/

	result = D3DXCreateSprite(d3ddev, &sprite_handler);
	if (result != D3D_OK)
		return 0;

	for (int i = 0; i < 3; i++)
	{
		sprintf_s(s, "Picture\\Player\\player_right%d.png", i + 1);
		player_image_right[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (player_image_right[i] == NULL)
			return 0;

		sprintf_s(s, "Picture\\Player\\player_left%d.png", i + 1);
		player_image_left[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (player_image_left[i] == NULL)
			return 0;

		sprintf_s(s, "Picture\\Player\\player_up%d.png", i + 1);
		player_image_up[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (player_image_up[i] == NULL)
			return 0;

		sprintf_s(s, "Picture\\Player\\player_down%d.png", i + 1);
		player_image_down[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (player_image_down[i] == NULL)
			return 0;
	}

	sprintf_s(s, "Picture\\background.png");
	background = LoadSurface(s, NULL);

	player_auto.x = 0;
	player_auto.y = 64;
	player_auto.width = 48;
	player_auto.height = 64;
	player_auto.curframe = 0;
	player_auto.lastframe = 2;
	player_auto.animdelay = 2;
	player_auto.animcount = 0;
	player_auto.movex = 4;
	player_auto.movey = 0;
	player_auto.direction = 6;

	player_control.x = 64;
	player_control.y = 64;
	player_control.width = 48;
	player_control.height = 64;
	player_control.curframe = 0;
	player_control.lastframe = 2;
	player_control.animdelay = 2;
	player_control.animcount = 0;
	player_control.movex = 0;
	player_control.movey = 0;
	player_control.direction = 6;
	//return okay
	return 1;
}

void Game_Run(HWND hwnd)
{
	if (d3ddev == NULL)
		return;

	/*Poll_Keyboard();*/

	if (GetTickCount() - start >= 30)
	{
		// Tái lập lại thời gian
		start = GetTickCount();

		////////////////////------------------AUTO--------------------///////////////////////////////
		// //
		// di chuyển sprite
		player_auto.x += player_auto.movex;
		player_auto.y += player_auto.movey;

		// Đóng gói sprite vào trong các khung màn hình
		if (player_auto.x == SCREEN_WIDTH - player_auto.width - 64 && player_auto.y == 64)
		{
			player_auto.movex = 0;
			player_auto.movey = 4;
		}

		if (player_auto.y == SCREEN_HEIGHT - player_auto.height - 16 && player_auto.x == SCREEN_WIDTH - player_auto.width - 64)
		{
			player_auto.movex = -4;
			player_auto.movey = 0;
		}

		if (player_auto.x == 64 && player_auto.y == SCREEN_HEIGHT - player_auto.height - 16)
		{
			player_auto.movex = 0;
			player_auto.movey = -4;
		}

		if (player_auto.y == 64 && player_auto.x == 64)
		{
			player_auto.movex = 4;
			player_auto.movey = 0;
		}

		// Có một animation delay
		if (++player_auto.animcount > player_auto.animdelay)
		{
			// Tái lập bộ đếm
			player_auto.animcount = 0;
			// Animation sprite
			if (++player_auto.curframe > player_auto.lastframe)
				player_auto.curframe = 0;
		}
		//
		////////////////////////------------------AUTO--------------------////////////////////////////

		////////////////////////------------------CONTROL--------------------////////////////////////////
		//
		if (KEY_DOWN(VK_LEFT))
		{
			if (player_control.x >= 64)
				player_control.x += player_control.movex;
			
			player_control.direction = 4;
			player_control.movex = -4;
			player_control.movey = 0;
		}
		else if (KEY_DOWN(VK_RIGHT))
		{
			if (player_control.x <= SCREEN_WIDTH - player_control.width - 64)
				player_control.x += player_control.movex;
			player_control.direction = 6;
			player_control.movex = 4;
			player_control.movey = 0;
		}
		else if (KEY_DOWN(VK_UP))
		{
			if (player_control.y >= 64)
				player_control.y += player_control.movey;
			player_control.direction = 8;
			player_control.movey = -4;
			player_control.movex = 0;
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			if (player_control.y <= SCREEN_HEIGHT - player_control.height - 16)
				player_control.y += player_control.movey;
			player_control.direction = 2;
			player_control.movey = 4;
			player_control.movex = 0;
		}
		else
		{
			player_control.movex = 0;
			player_control.movey = 0;
		}

		if (++player_control.animcount > player_control.animdelay)
		{
			// Tái lập bộ đếm
			player_control.animcount = 0;
			// Animation sprite
			if (++player_control.curframe > player_control.lastframe)
				player_control.curframe = 0;
		}

		//
		////////////////////////------------------CONTROL--------------------////////////////////////////
	}

	if (d3ddev->BeginScene())
	{
		// Xóa toàn bộ màn hình
		d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);

		// Bắt đầu Sprite Handler
		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

		////////////////////------------------AUTO--------------------///////////////////////////////
		// Tạo vector để cập nhật vị trí của sprite
		D3DXVECTOR3 position((float)player_auto.x, (float)player_auto.y, 0);

		if (player_auto.movex > 0)
			sprite_handler->Draw(
				player_image_right[player_auto.curframe],
				NULL,
				NULL,
				&position,
				D3DCOLOR_XRGB(255, 255, 255));

		if (player_auto.movex < 0)
			sprite_handler->Draw(
				player_image_left[player_auto.curframe],
				NULL,
				NULL,
				&position,
				D3DCOLOR_XRGB(255, 255, 255));

		if (player_auto.movey > 0)
			sprite_handler->Draw(
				player_image_down[player_auto.curframe],
				NULL,
				NULL,
				&position,
				D3DCOLOR_XRGB(255, 255, 255));

		if (player_auto.movey < 0)
			sprite_handler->Draw(
				player_image_up[player_auto.curframe],
				NULL,
				NULL,
				&position,
				D3DCOLOR_XRGB(255, 255, 255));
		// //
		////////////////////////------------------AUTO--------------------////////////////////////////

		////////////////////////------------------CONTROL--------------------////////////////////////////
		// //
		D3DXVECTOR3 position2((float)player_control.x, (float)player_control.y, 0);

		// player moving
		if (player_control.movex != 0 || player_control.movey != 0)
		{

			if (player_control.direction == 6)
				sprite_handler->Draw(
					player_image_right[player_control.curframe],
					NULL,
					NULL,
					&position2,
					D3DCOLOR_XRGB(255, 255, 255));

			if (player_control.direction == 4)
				sprite_handler->Draw(
					player_image_left[player_control.curframe],
					NULL,
					NULL,
					&position2,
					D3DCOLOR_XRGB(255, 255, 255));

			if (player_control.direction == 8)
				sprite_handler->Draw(
					player_image_up[player_control.curframe],
					NULL,
					NULL,
					&position2,
					D3DCOLOR_XRGB(255, 255, 255));

			if (player_control.direction == 2)
				sprite_handler->Draw(
					player_image_down[player_control.curframe],
					NULL,
					NULL,
					&position2,
					D3DCOLOR_XRGB(255, 255, 255));
		}
		else //player stop
		{
			if (player_control.direction == 6)
				sprite_handler->Draw(
					player_image_right[1],
					NULL,
					NULL,
					&position2,
					D3DCOLOR_XRGB(255, 255, 255));

			if (player_control.direction == 4)
				sprite_handler->Draw(
					player_image_left[1],
					NULL,
					NULL,
					&position2,
					D3DCOLOR_XRGB(255, 255, 255));

			if (player_control.direction == 8)
				sprite_handler->Draw(
					player_image_up[1],
					NULL,
					NULL,
					&position2,
					D3DCOLOR_XRGB(255, 255, 255));

			if (player_control.direction == 2)
				sprite_handler->Draw(
					player_image_down[1],
					NULL,
					NULL,
					&position2,
					D3DCOLOR_XRGB(255, 255, 255));
		}
		//
		////////////////////////------------------CONTROL--------------------////////////////////////////

		// Dừng vẽ
		sprite_handler->End();
		// Dừng render
		d3ddev->EndScene();
	}

	// Thể hiện back buffer lên màn hình
	d3ddev->Present(NULL, NULL, NULL, NULL);
	// Kiểm tra phím escape (để kết thúc chương trình)
	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);
}

void Game_End(HWND hwnd)
{
	int n;
	for (n = 0; n < 3; n++)
		if (player_image_right[n] != NULL)
			player_image_right[n]->Release();
	if (background != NULL)
		background->Release();
	if (sprite_handler != NULL)
		sprite_handler->Release();
}
