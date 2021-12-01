#include "game.h"
#include "dxgraphics.h"

LPDIRECT3DTEXTURE9 player_image_right[3];
LPDIRECT3DTEXTURE9 player_image_left[3];
LPDIRECT3DTEXTURE9 player_image_up[3];
LPDIRECT3DTEXTURE9 player_image_down[3];

LPDIRECT3DTEXTURE9 wheel_image[4];
LPDIRECT3DTEXTURE9 mid_wheel_image;
LPDIRECT3DTEXTURE9 sophia_body_image[6];
LPDIRECT3DTEXTURE9 sophia_gun_image[5];

LPDIRECT3DTEXTURE9 bug_gray_image[3];
LPDIRECT3DTEXTURE9 cam_gray_image[2];

SPRITE player_auto;
SPRITE player_control;

SOPHIA sophia;

SPRITE bug1;
SPRITE bug2;
SPRITE cam1;

LPD3DXSPRITE sprite_handler;
HRESULT result;

MAP map;
MAP map_area3_scene1;//1
MAP map_area3_scene2;//2
MAP map_dungeon;//3
CAM cam;

int mapid;
long start = GetTickCount();

int Game_Init(HWND hwnd)
{
	srand(time(NULL));
	char s[100];

	result = D3DXCreateSprite(d3ddev, &sprite_handler);
	if (result != D3D_OK)
		return 0;

	/////////////////
#pragma region Load Player image

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
#pragma endregion
	/////////////////

	/////////////////
#pragma region Load Sophia Image
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(s, "Picture\\Sophia\\wheel%d.png", i + 1);
		wheel_image[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (wheel_image[i] == NULL)
			return 0;
	}

	sprintf_s(s, "Picture\\Sophia\\wheel%d.png", 0);
	mid_wheel_image = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));

	sprintf_s(s, "Picture\\Sophia\\body%d_left.png", 1);
	sophia_body_image[0] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Sophia\\body%d_left.png", 2);
	sophia_body_image[1] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));

	sprintf_s(s, "Picture\\Sophia\\body%d_right.png", 1);
	sophia_body_image[3] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Sophia\\body%d_right.png", 2);
	sophia_body_image[2] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));

	sprintf_s(s, "Picture\\Sophia\\gun%d_left.png", 1);
	sophia_gun_image[0] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Sophia\\gun%d_left.png", 2);
	sophia_gun_image[1] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Sophia\\gunup.png");
	sophia_gun_image[2] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Sophia\\gun%d_right.png", 2);
	sophia_gun_image[3] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Sophia\\gun%d_right.png", 1);
	sophia_gun_image[4] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));

#pragma endregion
	/////////////////

	/////////////////
#pragma region Load Map Image

	for (int i = 0; i < 112; i++)
	{
		sprintf_s(s, "Picture\\Area3 tile set\\Area3_%d.png", i + 1);
		map_area3_scene1.image[i] = LoadSurface(s, NULL);
	}
	map_area3_scene1.height = 30 * 32;
	map_area3_scene1.width = 16 * 32;
	ifstream ifs("Area3_Scene1.txt");
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int num;
			ifs >> num;
			map_area3_scene1.matrix[i][j] = num;
		}
	}
	ifs.close();

	for (int i = 0; i < 76; i++)
	{
		sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon%d.png", i + 1);
		map_dungeon.image[i] = LoadSurface(s, NULL);
	}
	map_dungeon.height = 128 * 32;
	map_dungeon.width = 36 * 32;
	ifstream ifs1("Dungeon.txt");
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 36; j++)
		{
			int num;
			ifs1 >> num;
			map_dungeon.matrix[i][j] = num;
		}
	}
	ifs1.close();

#pragma endregion
	/////////////////

	/////////////////
#pragma region Load Enemy Image

	for (int i = 0; i < 3; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\bug%d.png", i + 1);
		bug_gray_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (bug_gray_image[i] == NULL)
			return 0;
	}
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\cam%d.png", i + 1);
		cam_gray_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (cam_gray_image[i] == NULL)
			return 0;
	}

#pragma endregion
	/////////////////

	/////////////////
#pragma region Parameter

	//set camera
	cam.x = 0;
	cam.y = 16;
	cam.movex = 0;
	cam.movey = 0;

	sophia.x = 128;
	sophia.y = 224;
	sophia.width = 48;
	sophia.height = 32;
	sophia.animcount = 0;
	sophia.animdelay = 2;
	sophia.direction = 6;
	sophia.movex = 0;
	sophia.movey = 4;
	sophia.Update_body();
	sophia.Update_wheel();
	sophia.wheelcurframe = 0;
	sophia.wheellastframe = 3;

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

	player_control.x = 216;
	player_control.y = 96;
	player_control.width = 48;
	player_control.height = 64;
	player_control.curframe = 0;
	player_control.lastframe = 2;
	player_control.animdelay = 2;
	player_control.animcount = 0;
	player_control.movex = 0;
	player_control.movey = 0;
	player_control.direction = 2;

	bug1.x = 64;
	bug1.y = 576;
	bug1.width = 40;
	bug1.height = 36;
	bug1.curframe = 0;
	bug1.lastframe = 2;
	bug1.animdelay = 5;
	bug1.animcount = 0;
	bug1.movex = 2;
	bug1.movey = 0;
	bug1.direction = 6;

	bug2.x = 352;
	bug2.y = 832;
	bug2.width = 40;
	bug2.height = 36;
	bug2.curframe = 0;
	bug2.lastframe = 2;
	bug2.animdelay = 5;
	bug2.animcount = 0;
	bug2.movex = 2;
	bug2.movey = 0;
	bug2.direction = 6;

	cam1.x = 64;
	cam1.y = 1600;
	cam1.width = 34;
	cam1.height = 36;
	cam1.curframe = 0;
	cam1.lastframe = 1;
	cam1.animdelay = 5;
	cam1.animcount = 0;
	cam1.movex = 2;
	cam1.movey = 0;
	cam1.direction = 6;
#pragma endregion
	/////////////////
	return 1;
}

void Game_Run(HWND hwnd)
{
	if (d3ddev == NULL)
		return;

	map = map_area3_scene1;
	mapid = 1;

	if (GetTickCount() - start >= 30)
	{
		// Tái lập lại thời gian
		start = GetTickCount();

		if (mapid == 3)
		{
			/////////////////////
#pragma region Update Player Control, and Cam

			/*if (KEY_DOWN(VK_LEFT) && KEY_DOWN(VK_DOWN))
			{
				player_control.movex = -4;
				player_control.movey = 4;
				cam.movey = 4;

				if (!map_dungeon.collide_left(player_control))
				{
					player_control.x += player_control.movex;
				}

				if (!map_dungeon.collide_down(player_control))
				{
					player_control.y += player_control.movey;
					if (cam.y < map_dungeon.height - SCREEN_HEIGHT - 32 && (player_control.y - cam.y) > SCREEN_HEIGHT / 2)
						cam.y += cam.movey;
				}
			}*/
			if (KEY_DOWN(VK_LEFT))
			{
				player_control.move_left();
				if (!map_dungeon.jason_collide_left(player_control))
				{
					player_control.x += player_control.movex;
				}
			}
			else if (KEY_DOWN(VK_RIGHT))
			{
				player_control.move_right();
				if (!map_dungeon.jason_collide_right(player_control))
					player_control.x += player_control.movex;
			}
			else if (KEY_DOWN(VK_UP))
			{
				player_control.move_up();
				cam.movey = -4;
				if (!map_dungeon.jason_collide_up(player_control))
				{
					player_control.y += player_control.movey;
					if (cam.y >= 16 && (player_control.y - cam.y) < SCREEN_HEIGHT / 2)
						cam.y += cam.movey;
				}
			}
			else if (KEY_DOWN(VK_DOWN))
			{
				player_control.move_down();
				cam.movey = 4;
				if (!map_dungeon.jason_collide_down(player_control))
				{
					player_control.y += player_control.movey;
					if (cam.y < map_dungeon.height - SCREEN_HEIGHT - 32 && (player_control.y - cam.y) > SCREEN_HEIGHT / 2)
						cam.y += cam.movey;
				}
			}
			else
			{
				cam.movey = 0;
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


#pragma endregion
			/////////////////////

			/////////////////////
#pragma region Update Player Auto

		// di chuyển sprite
			player_auto.x += player_auto.movex;
			player_auto.y += player_auto.movey;

			// Đóng gói sprite vào trong các khung màn hình
			if (player_auto.x == SCREEN_WIDTH - player_auto.width - 2 * TILE_SIZE && player_auto.y == 2 * TILE_SIZE)
			{
				player_auto.movex = 0;
				player_auto.movey = 4;
			}

			if (player_auto.y == 384 - player_auto.height && player_auto.x == SCREEN_WIDTH - player_auto.width - 2 * TILE_SIZE)
			{
				player_auto.movex = -4;
				player_auto.movey = 0;
			}

			if (player_auto.x == 2 * TILE_SIZE && player_auto.y == 384 - player_auto.height)
			{
				player_auto.movex = 0;
				player_auto.movey = -4;
			}

			if (player_auto.y == 2 * TILE_SIZE && player_auto.x == 2 * TILE_SIZE)
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
#pragma endregion
			/////////////////////

			/////////////////////
#pragma region Update Enemy

			bug1.x += bug1.movex;
			if (bug1.x >= SCREEN_WIDTH - bug1.width - 2 * TILE_SIZE)
			{
				bug1.movex = bug1.movex * (-1);
			}
			if (bug1.x <= 64)
			{
				bug1.movex = bug1.movex * (-1);
			}

			if (++bug1.animcount > bug1.animdelay)
			{
				bug1.animcount = 0;
				if (++bug1.curframe > bug1.lastframe)
					bug1.curframe = 0;
			}

			bug2.x += bug2.movex;
			if (bug2.x >= SCREEN_WIDTH - bug2.width - 2 * TILE_SIZE)
			{
				bug2.movex = bug2.movex * (-1);
			}
			if (bug2.x <= 64)
			{
				bug2.movex = bug2.movex * (-1);
			}

			if (++bug2.animcount > bug2.animdelay)
			{
				bug2.animcount = 0;
				if (++bug2.curframe > bug2.lastframe)
					bug2.curframe = 0;
			}

			cam1.x += cam1.movex;
			if (cam1.x >= SCREEN_WIDTH - cam1.width - 2 * TILE_SIZE)
			{
				cam1.movex = cam1.movex * (-1);
			}
			if (cam1.x <= 64)
			{
				cam1.movex = cam1.movex * (-1);
			}

			if (++cam1.animcount > cam1.animdelay)
			{
				cam1.animcount = 0;
				if (++cam1.curframe > cam1.lastframe)
					cam1.curframe = 0;
			}
#pragma endregion
			/////////////////////
		}
		else if (mapid == 1)
		{
#pragma region Update Sophia

			if (KEY_DOWN(VK_LEFT))
			{
				sophia.move_left();

				sophia.x += sophia.movex;
				sophia.Update_body();
				sophia.Update_wheel();
			}
			else if (KEY_DOWN(VK_RIGHT))
			{
				sophia.move_right();

				sophia.x += sophia.movex;
				sophia.Update_body();
				sophia.Update_wheel();
			}
			else
			{
				sophia.movex = 0;
			}

			if (++sophia.animcount > sophia.animdelay)
			{
				// Tái lập bộ đếm
				sophia.animcount = 0;
				// Animation sprite
				if (sophia.movex != 0)
					sophia.wheelcurframe++;
				if (sophia.wheelcurframe > sophia.wheellastframe)
					sophia.wheelcurframe = 0;
			}
#pragma endregion
		}
	}

	/////////////////////////
#pragma region Draw

	if (d3ddev->BeginScene())
	{
		// Bắt đầu Sprite Handler
		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

		if (mapid == 3)
		{
			////////////////
#pragma region Draw Player Auto

		// Tạo vector để cập nhật vị trí của sprite
			D3DXVECTOR3 position1((float)player_auto.x, (float)player_auto.y - cam.y, 0);

			if (player_auto.movex > 0)
				sprite_handler->Draw(
					player_image_right[player_auto.curframe],
					NULL,
					NULL,
					&position1,
					D3DCOLOR_XRGB(255, 255, 255));

			if (player_auto.movex < 0)
				sprite_handler->Draw(
					player_image_left[player_auto.curframe],
					NULL,
					NULL,
					&position1,
					D3DCOLOR_XRGB(255, 255, 255));

			if (player_auto.movey > 0)
				sprite_handler->Draw(
					player_image_down[player_auto.curframe],
					NULL,
					NULL,
					&position1,
					D3DCOLOR_XRGB(255, 255, 255));

			if (player_auto.movey < 0)
				sprite_handler->Draw(
					player_image_up[player_auto.curframe],
					NULL,
					NULL,
					&position1,
					D3DCOLOR_XRGB(255, 255, 255));

#pragma endregion
			////////////////

			///////////////////
#pragma region Draw Player Control

			D3DXVECTOR3 position2((float)player_control.x, (float)player_control.y - cam.y, 0);

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

#pragma endregion
			///////////////////

			///////////////////
#pragma region Draw Enemy

			D3DXVECTOR3 position3((float)bug1.x, (float)bug1.y - cam.y, 0);
			sprite_handler->Draw(
				bug_gray_image[bug1.curframe],
				NULL,
				NULL,
				&position3,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 position4((float)bug2.x, (float)bug2.y - cam.y, 0);
			sprite_handler->Draw(
				bug_gray_image[bug2.curframe],
				NULL,
				NULL,
				&position4,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 position5((float)cam1.x, (float)cam1.y - cam.y, 0);
			sprite_handler->Draw(
				cam_gray_image[cam1.curframe],
				NULL,
				NULL,
				&position5,
				D3DCOLOR_XRGB(255, 255, 255));

#pragma endregion
			///////////////////
		}
		else if (mapid == 1)
		{
#pragma region Draw Sophia
			D3DXVECTOR3 position1((float)sophia.body_x, (float)sophia.body_y - cam.y, 0);
			D3DXVECTOR3 position2((float)sophia.wheelleft_x, (float)sophia.wheelleft_y - cam.y, 0);
			D3DXVECTOR3 position3((float)sophia.wheelright_x, (float)sophia.wheelright_y - cam.y, 0);
			D3DXVECTOR3 position4((float)sophia.midwheel_x, (float)sophia.midwheel_y - cam.y, 0);
			D3DXVECTOR3 position5((float)sophia.gun_x, (float)sophia.gun_y - cam.y, 0);

			if (sophia.direction == 6)
			{
				sprite_handler->Draw(
					sophia_body_image[3],
					NULL,
					NULL,
					&position1,
					D3DCOLOR_XRGB(255, 255, 255));

				sprite_handler->Draw(
					sophia_gun_image[4],
					NULL,
					NULL,
					&position5,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			if (sophia.direction == 4)
			{
				sprite_handler->Draw(
					sophia_body_image[0],
					NULL,
					NULL,
					&position1,
					D3DCOLOR_XRGB(255, 255, 255));
				sprite_handler->Draw(
					sophia_gun_image[0],
					NULL,
					NULL,
					&position5,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			sprite_handler->Draw(
				wheel_image[sophia.wheelcurframe],
				NULL,
				NULL,
				&position2,
				D3DCOLOR_XRGB(255, 255, 255));
			sprite_handler->Draw(
				wheel_image[sophia.wheelcurframe],
				NULL,
				NULL,
				&position3,
				D3DCOLOR_XRGB(255, 255, 255));
			sprite_handler->Draw(
				mid_wheel_image,
				NULL,
				NULL,
				&position4,
				D3DCOLOR_XRGB(255, 255, 255));

#pragma endregion

		}

		////////////////
#pragma region Draw Map

		int offset_y = cam.y % TILE_SIZE;
		RECT rect_des;
		rect_des.top = 0;
		rect_des.bottom = rect_des.top + TILE_SIZE - offset_y;

		RECT rect_src;
		rect_src.top = offset_y;
		rect_src.bottom = TILE_SIZE;
		rect_src.left = 0;
		rect_src.right = TILE_SIZE;

		for (int j = 0; j < SCREEN_WIDTH / TILE_SIZE; j++)
		{
			rect_des.left = j * TILE_SIZE;
			rect_des.right = rect_des.left + TILE_SIZE;

			d3ddev->StretchRect(map.image[map.matrix[cam.y / TILE_SIZE][j] - 1],
				&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);
		}

		for (int i = cam.y / TILE_SIZE + 1; i < (SCREEN_HEIGHT + cam.y) / TILE_SIZE; i++)
		{
			rect_des.top = rect_des.bottom;
			rect_des.bottom = rect_des.top + TILE_SIZE;
			for (int j = 0; j < SCREEN_WIDTH / TILE_SIZE; j++)
			{
				rect_des.left = j * TILE_SIZE;
				rect_des.right = rect_des.left + TILE_SIZE;

				d3ddev->StretchRect(map.image[map.matrix[i][j] - 1],
					NULL, backbuffer, &rect_des, D3DTEXF_NONE);
			}
		}

		rect_src.top = 0;
		rect_src.bottom = rect_src.top + offset_y;

		rect_des.top = rect_des.bottom;
		rect_des.bottom = rect_des.top + offset_y;

		for (int j = 0; j < SCREEN_WIDTH / TILE_SIZE; j++)
		{
			rect_des.left = j * TILE_SIZE;
			rect_des.right = rect_des.left + TILE_SIZE;

			d3ddev->StretchRect(map.image[map.matrix[(SCREEN_HEIGHT + cam.y) / TILE_SIZE][j] - 1],
				&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);
		}
#pragma endregion
		////////////////

		// Dừng vẽ
		sprite_handler->End();
		// Dừng render
		d3ddev->EndScene();
	}

	// Thể hiện back buffer lên màn hình
	d3ddev->Present(NULL, NULL, NULL, NULL);
#pragma endregion
	/////////////////////////

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

	if (sprite_handler != NULL)
		sprite_handler->Release();
}
