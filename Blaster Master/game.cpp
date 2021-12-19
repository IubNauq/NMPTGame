#include "game.h"
#include "dxgraphics.h"

LPD3DXSPRITE sprite_handler;
HRESULT result;

LPDIRECT3DTEXTURE9 P_item_image[1];
vector<SPRITE> items_area3_scene1;
vector<SPRITE> items_area3_scene2;
vector<SPRITE> items_dungeon;

SPRITE jason;
LPDIRECT3DTEXTURE9 jason_image_right[3];
LPDIRECT3DTEXTURE9 jason_image_left[3];
LPDIRECT3DTEXTURE9 jason_image_up[3];
LPDIRECT3DTEXTURE9 jason_image_down[3];
LPDIRECT3DTEXTURE9 jason_bullet_image[4];
LPDIRECT3DTEXTURE9 jason_die_image[5];
vector<BULLET> jason_bullet;
LPDIRECT3DTEXTURE9 dungeon_bullet_explosion_image[2];
vector<SPRITE> jason_die;

SOPHIA sophia;
LPDIRECT3DTEXTURE9 sophia_wheel_image[4];
LPDIRECT3DTEXTURE9 sophia_mid_wheel_image;
LPDIRECT3DTEXTURE9 sophia_body_image[6];
LPDIRECT3DTEXTURE9 sophia_gun_image[5];
LPDIRECT3DTEXTURE9 sophia_bullet_image[3];
LPDIRECT3DTEXTURE9 sophia_explosion_image[2];
vector<BULLET> sophia_bullet;
vector<SPRITE> sophia_explosion;
LPDIRECT3DTEXTURE9 area3_bullet_explosion_image[4];

LPDIRECT3DTEXTURE9 hp_bar_image[9];

vector<SPRITE> explosion;

// Enemy in dungeon
LPDIRECT3DTEXTURE9 enemy_bug_gray_image[3];
LPDIRECT3DTEXTURE9 enemy_bug_red_image[3];
LPDIRECT3DTEXTURE9 enemy_cam_gray_image[2];

LPDIRECT3DTEXTURE9 dungeon_enemy_explosion_image[2];
vector<SPRITE> dungeon_enemy_explosion;

// Enemy in Area3
LPDIRECT3DTEXTURE9 enemy_ball_left_gray_image[3];
LPDIRECT3DTEXTURE9 enemy_ball_right_gray_image[3];
LPDIRECT3DTEXTURE9 enemy_globular_gray_image[5];
LPDIRECT3DTEXTURE9 enemy_teeth_left_gray_image[4];
LPDIRECT3DTEXTURE9 enemy_teeth_right_gray_image[4];

LPDIRECT3DTEXTURE9 enemy_drop_red_image[2];
LPDIRECT3DTEXTURE9 enemy_drop_bullet_image[1];
vector<SPRITE> enemy_drop_bullet;

LPDIRECT3DTEXTURE9 enemy_rocket_gray_image[2];

vector<SPRITE> Dungeon_Enemy;
vector<SPRITE> Area3_Scene1_Enemy;
vector<SPRITE> Area3_Scene2_Enemy;
SPRITE temp;

MAP map;
MAP map_area3_scene1;//1
MAP map_area3_scene2;//2
MAP map_dungeon;//3
int mapid;
LPDIRECT3DTEXTURE9 tilemap8;
LPDIRECT3DTEXTURE9 tilemap9;
LPDIRECT3DTEXTURE9 tilemap20;
LPDIRECT3DTEXTURE9 tilemap21;
LPDIRECT3DTEXTURE9 tilemap10;
LPDIRECT3DTEXTURE9 tilemap22;

LPDIRECT3DTEXTURE9 tilemap11;
LPDIRECT3DTEXTURE9 tilemap12;
LPDIRECT3DTEXTURE9 tilemap23;
LPDIRECT3DTEXTURE9 tilemap24;
LPDIRECT3DTEXTURE9 tilemap35;
LPDIRECT3DTEXTURE9 tilemap36;

int arr[] = { 12,28,76,100 };
int brr[] = { 20,60,92 };

CAM cam;

long start = GetTickCount();
long start_shoot = GetTickCount();
long char_start_get_hit = GetTickCount();
long enemy_start_get_hit = GetTickCount();

bool flag = 1; // using for jason bullet

int Game_Init(HWND hwnd)
{
	srand(time(NULL));
	char s[100];

	result = D3DXCreateSprite(d3ddev, &sprite_handler);
	if (result != D3D_OK)
		return 0;

	sprintf_s(s, "Picture\\Items\\P.png");
	P_item_image[0] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 0));
	if (P_item_image[0] == NULL)
		return 0;

#pragma region Load Jason Image

	for (int i = 0; i < 3; i++)
	{
		sprintf_s(s, "Picture\\Player\\player_right%d.png", i + 1);
		jason_image_right[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (jason_image_right[i] == NULL)
			return 0;

		sprintf_s(s, "Picture\\Player\\player_left%d.png", i + 1);
		jason_image_left[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (jason_image_left[i] == NULL)
			return 0;

		sprintf_s(s, "Picture\\Player\\player_up%d.png", i + 1);
		jason_image_up[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (jason_image_up[i] == NULL)
			return 0;

		sprintf_s(s, "Picture\\Player\\player_down%d.png", i + 1);
		jason_image_down[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (jason_image_down[i] == NULL)
			return 0;
	}

	sprintf_s(s, "Picture\\Bullet\\jason_bullet_left.png");
	jason_bullet_image[0] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Bullet\\jason_bullet_right.png");
	jason_bullet_image[1] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Bullet\\jason_bullet_up.png");
	jason_bullet_image[2] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Bullet\\jason_bullet_down.png");
	jason_bullet_image[3] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));

	for (int i = 0; i < 2; i++)
	{
		sprintf_s(s, "Picture\\Explosion\\Dungeon_Enemy_Explosion%d.png", i + 1);
		dungeon_enemy_explosion_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 255, 255));
		if (dungeon_enemy_explosion_image[i] == NULL)
			return 0;

		sprintf_s(s, "Picture\\Explosion\\dungeon_boom_%d.png", i + 1);
		dungeon_bullet_explosion_image[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (dungeon_bullet_explosion_image[i] == NULL)
			return 0;
	}

	for (int i = 0; i < 5; i++)
	{
		sprintf_s(s, "Picture\\Player\\jason_die_%d.png", i + 1);
		jason_die_image[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (jason_die_image[i] == NULL)
			return 0;
	}

#pragma endregion

#pragma region Load Sophia Image
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(s, "Picture\\Sophia\\wheel%d.png", i + 1);
		sophia_wheel_image[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (sophia_wheel_image[i] == NULL)
			return 0;
	}

	sprintf_s(s, "Picture\\Sophia\\wheel%d.png", 0);
	sophia_mid_wheel_image = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));

	sprintf_s(s, "Picture\\Sophia\\body%d_left.png", 1);
	sophia_body_image[0] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Sophia\\body%d_left.png", 2);
	sophia_body_image[1] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Sophia\\body%d_right.png", 1);
	sophia_body_image[3] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Sophia\\body%d_right.png", 2);
	sophia_body_image[2] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Sophia\\bodyup%d_left.png", 1);
	sophia_body_image[4] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Sophia\\bodyup%d_right.png", 1);
	sophia_body_image[5] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));

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

	sprintf_s(s, "Picture\\Bullet\\bullet_left.png");
	sophia_bullet_image[0] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Bullet\\bullet_right.png");
	sophia_bullet_image[1] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Bullet\\bullet_up.png");
	sophia_bullet_image[2] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));

	for (int i = 0; i < 4; i++)
	{
		sprintf_s(s, "Picture\\Explosion\\area3_boom_%d.png", i + 1);
		area3_bullet_explosion_image[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (area3_bullet_explosion_image[i] == NULL)
			return 0;
	}

	for (int i = 0; i < 9; i++)
	{
		sprintf_s(s, "Picture\\Items\\hp_%d.png", i);
		hp_bar_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 255, 255));
		if (hp_bar_image[i] == NULL)
			return 0;
	}

	for (int i = 0; i < 2; i++)
	{
		sprintf_s(s, "Picture\\Sophia\\sophia_explosion_%d.png", i + 1);
		sophia_explosion_image[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (sophia_explosion_image[i] == NULL)
			return 0;
	}

#pragma endregion

#pragma region Load Map Image
	// Area3 Scene1
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

	// Area3 Scene2
	for (int i = 0; i < 112; i++)
	{
		sprintf_s(s, "Picture\\Area3 tile set\\Area3_%d.png", i + 1);
		map_area3_scene2.image[i] = LoadSurface(s, NULL);
	}
	map_area3_scene2.height = 32 * 32;
	map_area3_scene2.width = 80 * 32;
	ifstream ifs2("Area3_Scene2.txt");
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			int num;
			ifs2 >> num;
			map_area3_scene2.matrix[i][j] = num;
		}
	}
	ifs2.close();

	// Dungeon
	for (int i = 0; i < 78; i++)
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

	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon8.png");
	tilemap8 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon9.png");
	tilemap9 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon20.png");
	tilemap20 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon21.png");
	tilemap21 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon10.png");
	tilemap10 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon22.png");
	tilemap22 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));

	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon11.png");
	tilemap11 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon12.png");
	tilemap12 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon23.png");
	tilemap23 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon24.png");
	tilemap24 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon35.png");
	tilemap35 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon36.png");
	tilemap36 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));

#pragma endregion

#pragma region Load Enemy Image

	for (int i = 0; i < 3; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\bug%d.png", i + 1);
		enemy_bug_gray_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (enemy_bug_gray_image[i] == NULL)
			return 0;
	}

	for (int i = 0; i < 3; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\bug_red%d.png", i + 1);
		enemy_bug_red_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (enemy_bug_red_image[i] == NULL)
			return 0;
	}

	for (int i = 0; i < 2; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\cam%d.png", i + 1);
		enemy_cam_gray_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (enemy_cam_gray_image[i] == NULL)
			return 0;
	}
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\enemy_drop%d.png", i + 1);
		enemy_drop_red_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
	}

	sprintf_s(s, "Picture\\Enemy\\enemy_drop_bullet.png");
	enemy_drop_bullet_image[0] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));

	for (int i = 0; i < 3; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\enemy_ball%d.png", i + 1);
		enemy_ball_left_gray_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (enemy_ball_left_gray_image[i] == NULL)
			return 0;
	}

	for (int i = 0; i < 5; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\enemy_globular%d.png", i + 1);
		enemy_globular_gray_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (enemy_globular_gray_image[i] == NULL)
			return 0;
	}

	for (int i = 0; i < 4; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\enemy_teeth%d.png", i + 1);
		enemy_teeth_left_gray_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (enemy_teeth_left_gray_image[i] == NULL)
			return 0;
	}

	sprintf_s(s, "Picture\\Enemy\\enemy_teeth11.png");
	enemy_teeth_right_gray_image[0] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
	if (enemy_teeth_right_gray_image[0] == NULL)
		return 0;
	sprintf_s(s, "Picture\\Enemy\\enemy_teeth22.png");
	enemy_teeth_right_gray_image[1] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
	if (enemy_teeth_right_gray_image[1] == NULL)
		return 0;
	sprintf_s(s, "Picture\\Enemy\\enemy_teeth33.png");
	enemy_teeth_right_gray_image[2] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
	if (enemy_teeth_right_gray_image[2] == NULL)
		return 0;
	sprintf_s(s, "Picture\\Enemy\\enemy_teeth44.png");
	enemy_teeth_right_gray_image[3] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
	if (enemy_teeth_right_gray_image[3] == NULL)
		return 0;

	for (int i = 0; i < 3; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\enemy_ball%d.png", i + 4);
		enemy_ball_right_gray_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (enemy_ball_right_gray_image[i] == NULL)
			return 0;
	}

	for (int i = 0; i < 2; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\enemy_rocket%d.png", i + 1);
		enemy_rocket_gray_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (enemy_rocket_gray_image[i] == NULL)
			return 0;
	}


#pragma endregion

#pragma region Parameter

	// Area3 Scene1
	map = map_dungeon;
	mapid = 3;

	cam.x = 0;
	cam.y = 32;

#pragma region Parameter of Character
	sophia.x = 128;
	sophia.y = 224;
	sophia.width = 48;
	sophia.height = 32;
	sophia.animcount = 0;
	sophia.animdelay = 2;
	sophia.direction = 6;
	sophia.movex = 0;
	sophia.movey = 1;
	sophia.Update_body();
	sophia.Update_wheel();
	sophia.wheelcurframe = 0;
	sophia.wheellastframe = 3;
	sophia.hp = 8;

	jason.x = 216;
	jason.y = 96;
	jason.width = 48;
	jason.height = 64;
	jason.curframe = 0;
	jason.lastframe = 2;
	jason.animdelay = 2;
	jason.animcount = 0;
	jason.movex = 0;
	jason.movey = 0;
	jason.direction = 2;
	jason.hp = 8;
#pragma endregion

#pragma region Parameter of Enemy in Area3 Scene1

	temp.id = 1;
	temp.x = 256;
	temp.y = 224;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 1;
	temp.image[0] = enemy_drop_red_image[0];
	temp.image[1] = enemy_drop_red_image[1];
	temp.isDraw = true;
	temp.hp = 5;
	temp.isFire = false;
	Area3_Scene1_Enemy.push_back(temp);

	temp.id = 2;
	temp.x = 320;
	temp.y = 352;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 1;
	temp.image[0] = enemy_drop_red_image[0];
	temp.image[1] = enemy_drop_red_image[1];
	temp.isDraw = true;
	temp.hp = 5;
	temp.isFire = false;
	Area3_Scene1_Enemy.push_back(temp);

	temp.id = 3;
	temp.x = 256;
	temp.y = 480;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 0;
	temp.image[0] = enemy_drop_red_image[0];
	temp.image[1] = enemy_drop_red_image[1];
	temp.isDraw = true;
	temp.hp = 5;
	temp.isFire = false;
	Area3_Scene1_Enemy.push_back(temp);

#pragma endregion

#pragma region Parameter of Enemy in Area3 Scene2
	temp.id = 1;
	temp.x = 2050;
	temp.y = 64;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 5;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.image[0] = enemy_ball_left_gray_image[0];
	temp.image[1] = enemy_ball_left_gray_image[1];
	temp.image[2] = enemy_ball_left_gray_image[2];
	temp.isDraw = true;
	temp.hp = 1;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 2;
	temp.x = 1632;
	temp.y = 256;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 4;
	temp.image[0] = enemy_globular_gray_image[0];
	temp.image[1] = enemy_globular_gray_image[1];
	temp.image[2] = enemy_globular_gray_image[2];
	temp.image[3] = enemy_globular_gray_image[3];
	temp.image[4] = enemy_globular_gray_image[4];
	temp.isDraw = true;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 3;
	temp.x = 2080;
	temp.y = 0;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 3;
	temp.image[0] = enemy_teeth_left_gray_image[0];
	temp.image[1] = enemy_teeth_left_gray_image[1];
	temp.image[2] = enemy_teeth_left_gray_image[2];
	temp.image[3] = enemy_teeth_left_gray_image[3];
	temp.isDraw = false;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 4;
	temp.x = 1408;
	temp.y = 384;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 4;
	temp.image[0] = enemy_globular_gray_image[0];
	temp.image[1] = enemy_globular_gray_image[1];
	temp.image[2] = enemy_globular_gray_image[2];
	temp.image[3] = enemy_globular_gray_image[3];
	temp.image[4] = enemy_globular_gray_image[4];
	temp.isDraw = true;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 5;
	temp.x = 1312;
	temp.y = 192;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 5;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.image[0] = enemy_ball_left_gray_image[0];
	temp.image[1] = enemy_ball_left_gray_image[1];
	temp.image[2] = enemy_ball_left_gray_image[2];
	temp.isDraw = true;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 6;
	temp.x = 960;
	temp.y = 576;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 4;
	temp.image[0] = enemy_globular_gray_image[0];
	temp.image[1] = enemy_globular_gray_image[1];
	temp.image[2] = enemy_globular_gray_image[2];
	temp.image[3] = enemy_globular_gray_image[3];
	temp.image[4] = enemy_globular_gray_image[4];
	temp.isDraw = true;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 7;
	temp.x = 800;
	temp.y = 0;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 3;
	temp.image[0] = enemy_teeth_right_gray_image[0];
	temp.image[1] = enemy_teeth_right_gray_image[1];
	temp.image[2] = enemy_teeth_right_gray_image[2];
	temp.image[3] = enemy_teeth_right_gray_image[3];
	temp.isDraw = false;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 8;
	temp.x = 512;
	temp.y = 0;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 3;
	temp.image[0] = enemy_teeth_right_gray_image[0];
	temp.image[1] = enemy_teeth_right_gray_image[1];
	temp.image[2] = enemy_teeth_right_gray_image[2];
	temp.image[3] = enemy_teeth_right_gray_image[3];
	temp.isDraw = false;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 9;
	temp.x = 128;
	temp.y = 640;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 4;
	temp.image[0] = enemy_globular_gray_image[0];
	temp.image[1] = enemy_globular_gray_image[1];
	temp.image[2] = enemy_globular_gray_image[2];
	temp.image[3] = enemy_globular_gray_image[3];
	temp.image[4] = enemy_globular_gray_image[4];
	temp.isDraw = true;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 10;
	temp.x = 736;
	temp.y = 832;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 5;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.image[0] = enemy_ball_right_gray_image[0];
	temp.image[1] = enemy_ball_right_gray_image[1];
	temp.image[2] = enemy_ball_right_gray_image[2];
	temp.isDraw = true;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 11;
	temp.x = 736;
	temp.y = 928;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 5;
	temp.curframe = 0;
	temp.lastframe = 1;
	temp.image[0] = enemy_rocket_gray_image[0];
	temp.image[1] = enemy_rocket_gray_image[1];
	temp.hp = 3;
	temp.isDraw = true;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 12;
	temp.x = 1184;
	temp.y = 864;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 4;
	temp.image[0] = enemy_globular_gray_image[0];
	temp.image[1] = enemy_globular_gray_image[1];
	temp.image[2] = enemy_globular_gray_image[2];
	temp.image[3] = enemy_globular_gray_image[3];
	temp.image[4] = enemy_globular_gray_image[4];
	temp.hp = 1;
	temp.isDraw = true;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 13;
	temp.x = 1248;
	temp.y = 928;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 5;
	temp.curframe = 0;
	temp.lastframe = 1;
	temp.image[0] = enemy_rocket_gray_image[0];
	temp.image[1] = enemy_rocket_gray_image[1];
	temp.isDraw = true;
	temp.hp = 3;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 14;
	temp.x = 1312;
	temp.y = 704;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 5;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.image[0] = enemy_ball_right_gray_image[0];
	temp.image[1] = enemy_ball_right_gray_image[1];
	temp.image[2] = enemy_ball_right_gray_image[2];
	temp.isDraw = true;
	temp.hp = 1;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 15;
	temp.x = 1568;
	temp.y = 768;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 4;
	temp.image[0] = enemy_globular_gray_image[0];
	temp.image[1] = enemy_globular_gray_image[1];
	temp.image[2] = enemy_globular_gray_image[2];
	temp.image[3] = enemy_globular_gray_image[3];
	temp.image[4] = enemy_globular_gray_image[4];
	temp.isDraw = true;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 16;
	temp.x = 1952;
	temp.y = 768;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 4;
	temp.image[0] = enemy_globular_gray_image[0];
	temp.image[1] = enemy_globular_gray_image[1];
	temp.image[2] = enemy_globular_gray_image[2];
	temp.image[3] = enemy_globular_gray_image[3];
	temp.image[4] = enemy_globular_gray_image[4];
	temp.isDraw = true;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 17;
	temp.x = 2016;
	temp.y = 768;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 4;
	temp.image[0] = enemy_globular_gray_image[0];
	temp.image[1] = enemy_globular_gray_image[1];
	temp.image[2] = enemy_globular_gray_image[2];
	temp.image[3] = enemy_globular_gray_image[3];
	temp.image[4] = enemy_globular_gray_image[4];
	temp.isDraw = true;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 18;
	temp.x = 1696;
	temp.y = 0;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 3;
	temp.image[0] = enemy_teeth_right_gray_image[0];
	temp.image[1] = enemy_teeth_right_gray_image[1];
	temp.image[2] = enemy_teeth_right_gray_image[2];
	temp.image[3] = enemy_teeth_right_gray_image[3];
	temp.isDraw = false;
	Area3_Scene2_Enemy.push_back(temp);

	temp.id = 19;
	temp.x = 1791;
	temp.y = 0;
	temp.width = 36;
	temp.height = 36;
	temp.animcount = 0;
	temp.animdelay = 2;
	temp.curframe = 0;
	temp.lastframe = 3;
	temp.image[0] = enemy_teeth_right_gray_image[0];
	temp.image[1] = enemy_teeth_right_gray_image[1];
	temp.image[2] = enemy_teeth_right_gray_image[2];
	temp.image[3] = enemy_teeth_right_gray_image[3];
	temp.isDraw = false;
	Area3_Scene2_Enemy.push_back(temp);
#pragma endregion

#pragma region Parameter of Enemy in Dungeon

	temp.id = 1;
	temp.x = 96;
	temp.y = 576;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_red_image[0];
	temp.image[1] = enemy_bug_red_image[1];
	temp.image[2] = enemy_bug_red_image[2];
	temp.hp = 3;
	Dungeon_Enemy.push_back(temp);

	temp.id = 2;
	temp.x = 352;
	temp.y = 672;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_gray_image[0];
	temp.image[1] = enemy_bug_gray_image[1];
	temp.image[2] = enemy_bug_gray_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 3;
	temp.x = 96;
	temp.y = 864;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_red_image[0];
	temp.image[1] = enemy_bug_red_image[1];
	temp.image[2] = enemy_bug_red_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 4;
	temp.x = 352;
	temp.y = 1120;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_gray_image[0];
	temp.image[1] = enemy_bug_gray_image[1];
	temp.image[2] = enemy_bug_gray_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 5;
	temp.x = 128;
	temp.y = 1344;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_red_image[0];
	temp.image[1] = enemy_bug_red_image[1];
	temp.image[2] = enemy_bug_red_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 6;
	temp.x = 352;
	temp.y = 1632;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_gray_image[0];
	temp.image[1] = enemy_bug_gray_image[1];
	temp.image[2] = enemy_bug_gray_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 7;
	temp.x = 128;
	temp.y = 1856;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_red_image[0];
	temp.image[1] = enemy_bug_red_image[1];
	temp.image[2] = enemy_bug_red_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 8;
	temp.x = 128;
	temp.y = 2176;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_red_image[0];
	temp.image[1] = enemy_bug_red_image[1];
	temp.image[2] = enemy_bug_red_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 9;
	temp.x = 352;
	temp.y = 2368;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_gray_image[0];
	temp.image[1] = enemy_bug_gray_image[1];
	temp.image[2] = enemy_bug_gray_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 10;
	temp.x = 192;
	temp.y = 2656;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_red_image[0];
	temp.image[1] = enemy_bug_red_image[1];
	temp.image[2] = enemy_bug_red_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 11;
	temp.x = 352;
	temp.y = 2848;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_red_image[0];
	temp.image[1] = enemy_bug_red_image[1];
	temp.image[2] = enemy_bug_red_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 12;
	temp.x = 128;
	temp.y = 2880;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_red_image[0];
	temp.image[1] = enemy_bug_red_image[1];
	temp.image[2] = enemy_bug_red_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 13;
	temp.x = 128;
	temp.y = 3168;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_gray_image[0];
	temp.image[1] = enemy_bug_gray_image[1];
	temp.image[2] = enemy_bug_gray_image[2];
	Dungeon_Enemy.push_back(temp);

	temp.id = 14;
	temp.x = 96;
	temp.y = 3392;
	temp.width = 40;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 2;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_bug_gray_image[0];
	temp.image[1] = enemy_bug_gray_image[1];
	temp.image[2] = enemy_bug_gray_image[2];
	Dungeon_Enemy.push_back(temp);
#pragma endregion

#pragma endregion

	return 1;
}

void Game_Run(HWND hwnd)
{
	if (d3ddev == NULL)
		return;

	if (GetTickCount() - start >= 30)
	{
		// Tái lập lại thời gian
		start = GetTickCount();

		if (mapid == 3)
		{
#pragma region Update Jason, and Cam

			if (jason.hp > 0)
			{
				for (int i = 0; i < jason_bullet.size(); i++)
				{

					if (jason_bullet[i].direction == 1)
					{
						jason_bullet[i].x += jason_bullet[i].movex;

						if (jason_bullet[i].up_down == true)
							jason_bullet[i].y += 48 * cos(float(jason_bullet[i].x - jason.x - jason.width) / 40 + 2.75);
						else
							jason_bullet[i].y += -48 * cos(float(jason_bullet[i].x - jason.x - jason.width) / 40 + 2.75);

					}
					else if (jason_bullet[i].direction == 0)
					{
						jason_bullet[i].x += jason_bullet[i].movex;

						if (jason_bullet[i].up_down == true)
							jason_bullet[i].y += 48 * cos(float(jason_bullet[i].x - jason.x) / 40 - 2.75);
						else
							jason_bullet[i].y += -48 * cos(float(jason_bullet[i].x - jason.x) / 40 - 2.75);
					}
					else if (jason_bullet[i].direction == 2)
					{
						jason_bullet[i].y += jason_bullet[i].movey;

						if (jason_bullet[i].up_down == true)
							jason_bullet[i].x += 48 * cos(float(jason_bullet[i].y - jason.y) / 40 - 2.75);
						else
							jason_bullet[i].x += -48 * cos(float(jason_bullet[i].y - jason.y) / 40 - 2.75);
					}
					else if (jason_bullet[i].direction == 3)
					{
						jason_bullet[i].y += jason_bullet[i].movey;

						if (jason_bullet[i].up_down == true)
							jason_bullet[i].x += 48 * cos(float(jason_bullet[i].y - jason.y - jason.height) / 40 + 2.75);
						else
							jason_bullet[i].x += -48 * cos(float(jason_bullet[i].y - jason.y - jason.height) / 40 + 2.75);
					}
				}

				// Jason shoot
				if (KEY_DOWN(0x43))
				{
					if (jason_bullet.size() < 1000)
						if (GetTickCount() - start_shoot >= 100)
						{
							// Tái lập lại thời gian
							start_shoot = GetTickCount();
							BULLET bullet;
							bullet.up_down = flag;

							if (flag == true)
								flag = false;
							else
								flag = true;

							if (jason.direction == 6)
							{
								bullet.width = 18;
								bullet.height = 32;
								bullet.x = jason.x + jason.width;
								bullet.y = jason.y + jason.height / 2;

								bullet.movex = 24;
								bullet.movey = 0;
								bullet.direction = 1;
							}
							else if (jason.direction == 4)
							{
								bullet.width = 18;
								bullet.height = 32;
								bullet.x = jason.x;
								bullet.y = jason.y + jason.height / 2;
								bullet.movex = -24;
								bullet.movey = 0;
								bullet.direction = 0;
							}
							else if (jason.direction == 8)
							{
								bullet.width = 14;
								bullet.height = 32;
								bullet.x = jason.x + jason.width / 2;
								bullet.y = jason.y;
								bullet.movex = 0;
								bullet.movey = -24;
								bullet.direction = 2;
							}
							else if (jason.direction == 2)
							{
								bullet.width = 14;
								bullet.height = 32;
								bullet.x = jason.x + jason.width / 2;
								bullet.y = jason.y + jason.height;
								bullet.movex = 0;
								bullet.movey = 24;
								bullet.direction = 3;
							}

							jason_bullet.push_back(bullet);
						}
				}

				if (KEY_DOWN(VK_LEFT))
				{
					jason.move_left();
					if (!map_dungeon.jason_collide_left(jason))
					{
						jason.x += jason.movex;
						if (jason.x - cam.x - 32 < SCREEN_HEIGHT / 2 && cam.x > 0 && cam.y >= 3520)
							cam.x += jason.movex;
					}
				}
				else if (KEY_DOWN(VK_RIGHT))
				{
					jason.move_right();
					if (!map_dungeon.jason_collide_right(jason))
					{
						jason.x += jason.movex;
						if (jason.x - cam.x - 32 > SCREEN_HEIGHT / 2 && cam.x < map.width - 32 - SCREEN_WIDTH && cam.y >= 3520)
							cam.x += jason.movex;
					}
				}
				else if (KEY_DOWN(VK_UP))
				{
					jason.move_up();
					if (!map_dungeon.jason_collide_up(jason))
					{
						jason.y += jason.movey;
						if (cam.y >= 16 && (jason.y - cam.y) < SCREEN_HEIGHT / 2)
							cam.y += jason.movey;
					}
				}
				else if (KEY_DOWN(VK_DOWN))
				{
					jason.move_down();
					if (!map_dungeon.jason_collide_down(jason))
					{
						jason.y += jason.movey;
						if (cam.y < map_dungeon.height - SCREEN_HEIGHT - 32 && (jason.y - cam.y) > SCREEN_HEIGHT / 2)
							cam.y += jason.movey;
					}
				}
				else
				{
					jason.movex = 0;
					jason.movey = 0;
				}

				// Jason collide with trap
				if (map.jason_collide_trap_down(jason) ||
					map.jason_collide_trap_right(jason) ||
					map.jason_collide_trap_left(jason) ||
					map.jason_collide_trap_up(jason))
				{
					if (GetTickCount() - char_start_get_hit >= 500)
					{
						char_start_get_hit = GetTickCount();
						jason.hp -= 1;
					}
				}

				for (int i = 0; i < jason_bullet.size(); i++)
				{
					if (jason_bullet[i].x < cam.x || jason_bullet[i].x > cam.x + SCREEN_WIDTH ||
						jason_bullet[i].y < cam.y || jason_bullet[i].y > cam.y + SCREEN_HEIGHT)
						jason_bullet.erase(jason_bullet.begin() + i);

					else if (map.jason_bullet_collide_right(jason_bullet[i]) ||
						map.jason_bullet_collide_left(jason_bullet[i]) ||
						map.jason_bullet_collide_up(jason_bullet[i]) ||
						map.jason_bullet_collide_down(jason_bullet[i]))
					{
						SPRITE ex_temp;
						ex_temp.x = jason_bullet[i].x;
						ex_temp.y = jason_bullet[i].y;
						ex_temp.curframe = 0;
						ex_temp.lastframe = 1;
						ex_temp.animcount = 0;
						ex_temp.animdelay = 2;
						explosion.push_back(ex_temp);
					}
				}

				if (++jason.animcount > jason.animdelay)
				{
					// Tái lập bộ đếm
					jason.animcount = 0;
					// Animation sprite
					if (++jason.curframe > jason.lastframe)
						jason.curframe = 0;
				}

				for (int i = 0; i < explosion.size(); i++)
				{
					if (++explosion[i].animcount > explosion[i].animdelay)
					{
						explosion[i].animcount = 0;
						if (++explosion[i].curframe > explosion[i].lastframe)
							explosion.erase(explosion.begin() + i);
					}
				}

				for (int i = 0; i < items_dungeon.size(); i++)
				{
					if (items_dungeon[i].Jason_collide(jason))
					{
						items_dungeon.erase(items_dungeon.begin() + i);
						if (jason.hp < 8)
							jason.hp += 1;
					}
				}
			}
			else
			{
				if (jason.hp == 0)
				{
					SPRITE die_temp;
					die_temp.x = jason.x;
					die_temp.y = jason.y;
					die_temp.curframe = 0;
					die_temp.lastframe = 4;
					die_temp.animcount = 0;
					die_temp.animdelay = 2;
					jason_die.push_back(die_temp);
					jason.hp--;
				}

				for (int i = 0; i < jason_die.size(); i++)
				{
					if (++jason_die[i].animcount > jason_die[i].animdelay)
					{
						jason_die[i].animcount = 0;
						if (++jason_die[i].curframe > jason_die[i].lastframe)
							jason_die.erase(jason_die.begin() + i);
					}
				}
			}
#pragma endregion

#pragma region Update Enemy Dungeon

			for (int i = 0; i < Dungeon_Enemy.size(); i++)
			{
				// jason get hit by enemy
				if (Dungeon_Enemy[i].Jason_collide(jason) && GetTickCount() - char_start_get_hit >= 1000)
				{
					char_start_get_hit = GetTickCount();
					jason.hp--;
				}
				// enemy get hit by bullet
				for (int j = 0; j < jason_bullet.size(); j++)
				{
					if (Dungeon_Enemy[i].Bullet_collide(jason_bullet[j]) && GetTickCount() - enemy_start_get_hit >= 30)
					{
						enemy_start_get_hit = GetTickCount();
						Dungeon_Enemy[i].hp--;
						if (Dungeon_Enemy[i].hp == 0)
						{
							SPRITE ex_temp;
							ex_temp.x = Dungeon_Enemy[i].x;
							ex_temp.y = Dungeon_Enemy[i].y;
							ex_temp.curframe = 0;
							ex_temp.lastframe = 1;
							ex_temp.animcount = 0;
							ex_temp.animdelay = 2;
							dungeon_enemy_explosion.push_back(ex_temp);

							// Enemy drop item
							int random = 1 + rand() % (2 + 1 - 1);
							if (random == 1)
							{
								SPRITE item_temp;
								item_temp.x = Dungeon_Enemy[i].x;
								item_temp.y = Dungeon_Enemy[i].y;
								item_temp.width = 32;
								item_temp.height = 32;
								items_dungeon.push_back(item_temp);
							}

							Dungeon_Enemy.erase(Dungeon_Enemy.begin() + i);
						}
						jason_bullet.erase(jason_bullet.begin() + j);
						break;
					}
				}
			}

			for (int i = 0; i < Dungeon_Enemy.size(); i++)
			{
				if (++Dungeon_Enemy[i].animcount > Dungeon_Enemy[i].animdelay)
				{
					Dungeon_Enemy[i].animcount = 0;
					if (++Dungeon_Enemy[i].curframe > Dungeon_Enemy[i].lastframe)
						Dungeon_Enemy[i].curframe = 0;
				}

				// Enemy behaviour
				if (Dungeon_Enemy[i].id <= 14)
				{
					float a = jason.x - Dungeon_Enemy[i].x;
					float b = jason.y - Dungeon_Enemy[i].y;

					if (abs(a) <= 336 && abs(b) <= 336)
					{
						if (a > 0)
						{
							Dungeon_Enemy[i].movex = sqrt(4 / (1 + (b * b) / (a * a)));
							Dungeon_Enemy[i].movey = (b / a) * Dungeon_Enemy[i].movex;
						}
						else if (a < 0)
						{
							Dungeon_Enemy[i].movex = -sqrt(4 / (1 + (b * b) / (a * a)));
							Dungeon_Enemy[i].movey = (b / a) * Dungeon_Enemy[i].movex;
						}

						if (Dungeon_Enemy[i].movex > 0)
						{
							if (!map.jason_collide_right(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].x += Dungeon_Enemy[i].movex;
						}
						else if (Dungeon_Enemy[i].movex < 0)
						{
							if (!map.jason_collide_left(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].x += Dungeon_Enemy[i].movex;
						}

						if (Dungeon_Enemy[i].movey > 0)
						{
							if (!map.jason_collide_down(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].y += Dungeon_Enemy[i].movey;
						}
						else if (Dungeon_Enemy[i].movey < 0)
						{
							if (!map.jason_collide_up(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].y += Dungeon_Enemy[i].movey;
						}
					}
				}
			}

			for (int i = 0; i < dungeon_enemy_explosion.size(); i++)
			{
				if (++dungeon_enemy_explosion[i].animcount > dungeon_enemy_explosion[i].animdelay)
				{
					dungeon_enemy_explosion[i].animcount = 0;
					if (++dungeon_enemy_explosion[i].curframe > dungeon_enemy_explosion[i].lastframe)
						dungeon_enemy_explosion.erase(dungeon_enemy_explosion.begin() + i);
				}
			}

#pragma endregion
		}
		else if (mapid == 1 || mapid == 2)
		{
#pragma region Update Sophia and Cam
			// Sophia alive
			if (sophia.hp > 0)
			{
				if (map.sophia_collide_down(sophia))
				{
					sophia.movey = 0;
					// Sophia Jump
					if (KEY_DOWN(VK_SPACE))
					{
						sophia.movey = -16;
					}
				}
				else if (map.sophia_collide_up(sophia))
				{
					// Sophia Bounce top
					sophia.movey = 6;
				}
				else
				{
					// Sophia falling
					sophia.movey += 1;
					if (sophia.movey >= 8)
						sophia.movey = 8;
				}
				sophia.y += sophia.movey;
				sophia.Update_body();
				sophia.Update_wheel();

				// Update Cam
				if (sophia.movey > 0)
				{
					if (cam.y < map.height - SCREEN_HEIGHT - 16 && (sophia.y - cam.y) > SCREEN_HEIGHT / 2)
						cam.y += sophia.movey;
				}
				else if (sophia.movey < 0)
				{
					if (cam.y >= 16 && (sophia.y - cam.y) < SCREEN_HEIGHT / 2)
						cam.y += sophia.movey;
				}

				// Update bullet pos
				for (int i = 0; i < sophia_bullet.size(); i++)
				{
					sophia_bullet[i].x += sophia_bullet[i].movex;
					sophia_bullet[i].y += sophia_bullet[i].movey;
				}

				// "C" key pressed, then shoot
				if (KEY_DOWN(0x43))
				{
					if (sophia_bullet.size() < 3)
						if (GetTickCount() - start_shoot >= 100)
						{
							// Tái lập lại thời gian
							start_shoot = GetTickCount();
							BULLET bullet;

							if (sophia.direction == 6)
							{
								bullet.width = 48;
								bullet.height = 16;
								bullet.x = sophia.x;
								bullet.y = sophia.y;
								bullet.movex = 12;
								bullet.movey = 0;
								bullet.direction = 1;
							}
							else if (sophia.direction == 4)
							{
								bullet.width = 48;
								bullet.height = 16;
								bullet.x = sophia.x;
								bullet.y = sophia.y;
								bullet.movex = -12;
								bullet.movey = 0;
								bullet.direction = 0;
							}
							else if (sophia.direction == 48 || sophia.direction == 68)
							{
								bullet.width = 16;
								bullet.height = 48;
								bullet.x = sophia.x + 16;
								bullet.y = sophia.y - 16;
								bullet.movex = 0;
								bullet.movey = -12;
								bullet.direction = 2;
							}
							sophia_bullet.push_back(bullet);
						}
				}

				// Bullet go out of cam or collide with wall
				for (int i = 0; i < sophia_bullet.size(); i++)
				{
					if (sophia_bullet[i].movex != 0)
					{
						if (sophia_bullet[i].x < cam.x || sophia_bullet[i].x > cam.x + SCREEN_WIDTH)
						{
							sophia_bullet.erase(sophia_bullet.begin() + i);
						}
						else if (map.sophia_bullet_collide_left(sophia_bullet[i]) || map.sophia_bullet_collide_right(sophia_bullet[i]))
						{
							SPRITE ex_temp;
							if (sophia_bullet[i].movex < 0)
							{
								ex_temp.x = sophia_bullet[i].x;
								ex_temp.y = sophia_bullet[i].y;
								ex_temp.curframe = 1;
								ex_temp.lastframe = 3;
								ex_temp.animcount = 0;
								ex_temp.animdelay = 2;
							}
							else
							{
								ex_temp.x = sophia_bullet[i].x + sophia_bullet[i].width - 32;
								ex_temp.y = sophia_bullet[i].y;
								ex_temp.curframe = 1;
								ex_temp.lastframe = 3;
								ex_temp.animcount = 0;
								ex_temp.animdelay = 2;
							}
							explosion.push_back(ex_temp);

							sophia_bullet.erase(sophia_bullet.begin() + i);
						}
					}
					else if (sophia_bullet[i].movey != 0)
					{
						if (sophia_bullet[i].y < cam.y)
						{
							sophia_bullet.erase(sophia_bullet.begin() + i);
						}
						else if (map.sophia_bullet_collide_up(sophia_bullet[i]))
						{
							SPRITE ex_temp;
							ex_temp.x = sophia_bullet[i].x;
							ex_temp.y = sophia_bullet[i].y;
							ex_temp.curframe = 1;
							ex_temp.lastframe = 3;
							ex_temp.animcount = 0;
							ex_temp.animdelay = 2;
							explosion.push_back(ex_temp);

							sophia_bullet.erase(sophia_bullet.begin() + i);
						}
					}
				}

				if (KEY_DOWN(VK_UP) && KEY_DOWN(VK_LEFT))
				{
					sophia.move_left_up();

					if (!map.sophia_collide_left(sophia))
					{
						sophia.x += sophia.movex;
						sophia.Update_body();
						sophia.Update_wheel();

						if (sophia.x - cam.x - 32 < SCREEN_HEIGHT / 2 && cam.x > 32)
							cam.x += sophia.movex;
					}
				}
				else if (KEY_DOWN(VK_UP) && KEY_DOWN(VK_RIGHT))
				{
					sophia.move_right_up();

					if (!map.sophia_collide_right(sophia))
					{
						sophia.x += sophia.movex;
						sophia.Update_body();
						sophia.Update_wheel();

						if (sophia.x - cam.x - 32 > SCREEN_HEIGHT / 2 && cam.x < map.width - 32 - SCREEN_WIDTH)
							cam.x += sophia.movex;
					}
				}
				else if (KEY_DOWN(VK_UP))
				{
					if (sophia.direction == 4)
					{
						sophia.direction = 48;
						sophia.Update_body();
						sophia.Update_wheel();

					}
					if (sophia.direction == 6)
					{
						sophia.direction = 68;
						sophia.Update_body();
						sophia.Update_wheel();
					}
				}
				else if (KEY_DOWN(VK_LEFT))
				{
					sophia.move_left();

					if (!map.sophia_collide_left(sophia))
					{
						sophia.x += sophia.movex;
						sophia.Update_body();
						sophia.Update_wheel();

						if (sophia.x - cam.x - 32 < SCREEN_HEIGHT / 2 && cam.x > 32)
							cam.x += sophia.movex;
					}
				}
				else if (KEY_DOWN(VK_RIGHT))
				{
					sophia.move_right();

					if (!map.sophia_collide_right(sophia))
					{
						sophia.x += sophia.movex;
						sophia.Update_body();
						sophia.Update_wheel();

						if (sophia.x - cam.x - 32 > SCREEN_HEIGHT / 2 && cam.x < map.width - 32 - SCREEN_WIDTH)
							cam.x += sophia.movex;
					}
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
					if (sophia.movex > 0)
						sophia.wheelcurframe++;
					else if (sophia.movex < 0)
						sophia.wheelcurframe--;

					if (sophia.wheelcurframe > sophia.wheellastframe)
						sophia.wheelcurframe = 0;
					else if (sophia.wheelcurframe < 0)
						sophia.wheelcurframe = 3;
				}

				for (int i = 0; i < explosion.size(); i++)
				{
					if (++explosion[i].animcount > explosion[i].animdelay)
					{
						explosion[i].animcount = 0;
						if (++explosion[i].curframe > explosion[i].lastframe)
							explosion.erase(explosion.begin() + i);
					}
				}

				// sophia get an item
				for (int i = 0; i < items_area3_scene1.size(); i++)
				{
					if (items_area3_scene1[i].Sophia_collide(sophia))
					{
						items_area3_scene1.erase(items_area3_scene1.begin() + i);
						if (sophia.hp < 8)
							sophia.hp += 1;
					}
				}
				for (int i = 0; i < items_area3_scene2.size(); i++)
				{
					if (items_area3_scene2[i].Sophia_collide(sophia))
					{
						items_area3_scene2.erase(items_area3_scene2.begin() + i);
						if (sophia.hp < 8)
							sophia.hp += 1;
					}
				}
			}
			// Sophia die
			else
			{
				if (sophia.hp == 0)
				{
					SPRITE ex_temp;
					ex_temp.x = sophia.x - 32;
					ex_temp.y = sophia.y - 32;
					ex_temp.curframe = 0;
					ex_temp.lastframe = 1;
					ex_temp.animcount = 0;
					ex_temp.animdelay = 2;
					sophia_explosion.push_back(ex_temp);
					sophia.hp--;
				}

				for (int i = 0; i < sophia_explosion.size(); i++)
				{
					if (++sophia_explosion[i].animcount > sophia_explosion[i].animdelay)
					{
						sophia_explosion[i].animcount = 0;
						if (++sophia_explosion[i].curframe > sophia_explosion[i].lastframe)
							sophia_explosion.erase(sophia_explosion.begin() + i);
					}
				}
			}
#pragma endregion
		}

		if (mapid == 1)
		{
#pragma region Update Enemy Area3 Scene1, Tele

			if (map.sophia_collide_tele1(sophia))
			{
				map = map_area3_scene2;
				mapid = 2;

				cam.x = 2016;
				cam.y = 32;
				sophia.x = 2368;
				sophia.y = 256;
			}

			for (int i = 0; i < Area3_Scene1_Enemy.size(); i++)
			{
				// sophia get hit by enemy
				if (Area3_Scene1_Enemy[i].Sophia_collide(sophia) && GetTickCount() - char_start_get_hit >= 1000)
				{
					char_start_get_hit = GetTickCount();
					sophia.hp -= 1;
				}

				// Enemy Drop red behaviour
				if (sophia.y > Area3_Scene1_Enemy[i].y && Area3_Scene1_Enemy[i].isFire == false)
					if (sophia.x< Area3_Scene1_Enemy[i].x + Area3_Scene1_Enemy[i].width &&
						sophia.x + sophia.width>Area3_Scene1_Enemy[i].x)
					{
						Area3_Scene1_Enemy[i].curframe = 1;
						Area3_Scene1_Enemy[i].isFire = true;

						SPRITE bullet_temp;
						bullet_temp.x = Area3_Scene1_Enemy[i].x + 13;
						bullet_temp.y = Area3_Scene1_Enemy[i].y;
						bullet_temp.movey = 2;
						bullet_temp.width = 18;
						bullet_temp.height = 18;
						enemy_drop_bullet.push_back(bullet_temp);
					}

				// enemy get hit by sophia bullet
				for (int j = 0; j < sophia_bullet.size(); j++)
				{
					if (Area3_Scene1_Enemy[i].Bullet_collide(sophia_bullet[j]) && GetTickCount() - enemy_start_get_hit >= 30)
					{
						enemy_start_get_hit = GetTickCount();
						Area3_Scene1_Enemy[i].hp--;
						if (Area3_Scene1_Enemy[i].hp == 0)
						{
							SPRITE ex_temp;
							ex_temp.x = Area3_Scene1_Enemy[i].x;
							ex_temp.y = Area3_Scene1_Enemy[i].y;
							ex_temp.curframe = 0;
							ex_temp.lastframe = 3;
							ex_temp.animcount = 0;
							ex_temp.animdelay = 2;
							explosion.push_back(ex_temp);

							// Enemy drop item
							int random = 1 + rand() % (2 + 1 - 1);
							if (random == 1)
							{
								SPRITE item_temp;
								item_temp.x = Area3_Scene1_Enemy[i].x;
								item_temp.y = Area3_Scene1_Enemy[i].y;
								item_temp.width = 32;
								item_temp.height = 32;
								items_area3_scene1.push_back(item_temp);
							}

							Area3_Scene1_Enemy.erase(Area3_Scene1_Enemy.begin() + i);
						}
						sophia_bullet.erase(sophia_bullet.begin() + j);
						break;
					}
				}
			}

			for (int i = 0; i < enemy_drop_bullet.size(); i++)
			{
				if (enemy_drop_bullet[i].Sophia_collide(sophia))
				{
					sophia.hp -= 1;
					enemy_drop_bullet.erase(enemy_drop_bullet.begin() + i);
					break;
				}
				if (enemy_drop_bullet[i].y > cam.y + SCREEN_HEIGHT)
				{
					enemy_drop_bullet.erase(enemy_drop_bullet.begin() + i);
					break;
				}

				enemy_drop_bullet[i].y += enemy_drop_bullet[i].movey;
				enemy_drop_bullet[i].movey += 2;
				if (enemy_drop_bullet[i].movey >= 8)
					enemy_drop_bullet[i].movey = 8;
			}

#pragma endregion
		}
		else if (mapid == 2)
		{
#pragma region Update Enemy Area3 Scene2, Tele2

			if (map.sophia_collide_tele2(sophia))
			{
				map = map_dungeon;
				mapid = 3;

				cam.x = 0;
				cam.y = 16;
			}

			for (int i = 0; i < Area3_Scene2_Enemy.size(); i++)
			{
				// sophia get hit
				if (Area3_Scene2_Enemy[i].Sophia_collide(sophia) && GetTickCount() - char_start_get_hit >= 1000)
				{
					char_start_get_hit = GetTickCount();
					sophia.hp -= 1;
				}

				for (int j = 0; j < sophia_bullet.size(); j++)
				{

					if (Area3_Scene2_Enemy[i].Bullet_collide(sophia_bullet[j]) && GetTickCount() - enemy_start_get_hit >= 30)
					{
						enemy_start_get_hit = GetTickCount();
						Area3_Scene2_Enemy[i].hp--;
						if (Area3_Scene2_Enemy[i].hp == 0)
						{

							SPRITE ex_temp;
							ex_temp.x = Area3_Scene2_Enemy[i].x;
							ex_temp.y = Area3_Scene2_Enemy[i].y;
							ex_temp.curframe = 0;
							ex_temp.lastframe = 3;
							ex_temp.animcount = 0;
							ex_temp.animdelay = 2;
							explosion.push_back(ex_temp);

							// Enemy drop item
							int random = 1 + rand() % (2 + 1 - 1);
							if (random == 1)
							{
								SPRITE item_temp;
								item_temp.x = Area3_Scene2_Enemy[i].x;
								item_temp.y = Area3_Scene2_Enemy[i].y;
								item_temp.width = 32;
								item_temp.height = 32;
								items_area3_scene2.push_back(item_temp);
							}

							Area3_Scene2_Enemy.erase(Area3_Scene2_Enemy.begin() + i);
						}
						sophia_bullet.erase(sophia_bullet.begin() + j);
						break;
					}
				}
			}

			for (int i = 0; i < Area3_Scene2_Enemy.size(); i++)
			{
				if (++Area3_Scene2_Enemy[i].animcount > Area3_Scene2_Enemy[i].animdelay)
				{
					Area3_Scene2_Enemy[i].animcount = 0;
					if (++Area3_Scene2_Enemy[i].curframe > Area3_Scene2_Enemy[i].lastframe)
						Area3_Scene2_Enemy[i].curframe = 0;
				}

				// Enemy Behavior
				switch (Area3_Scene2_Enemy[i].id)
				{
				case 2:
					if (Area3_Scene2_Enemy[i].x <= 1632)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 1792)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 3:
					if (sophia.x < 1824) Area3_Scene2_Enemy[i].isDraw = true;
					if (Area3_Scene2_Enemy[i].isDraw == true)
					{
						Area3_Scene2_Enemy[i].x += -5;
						Area3_Scene2_Enemy[i].y = 368 + 48 * cos(float(Area3_Scene2_Enemy[i].x) / 32);
						if (Area3_Scene2_Enemy[i].x < cam.x)
							Area3_Scene2_Enemy.erase(Area3_Scene2_Enemy.begin() + i);
					}
					break;
				case 4:
					if (Area3_Scene2_Enemy[i].x <= 1408)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 1568)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 6:
					if (Area3_Scene2_Enemy[i].x <= 960)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 1088)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 7:
					if (sophia.x < 1088) Area3_Scene2_Enemy[i].isDraw = true;
					if (Area3_Scene2_Enemy[i].isDraw == true)
					{
						Area3_Scene2_Enemy[i].x += 5;
						Area3_Scene2_Enemy[i].y = 560 + 48 * cos(float(Area3_Scene2_Enemy[i].x) / 32);
						if (Area3_Scene2_Enemy[i].x > cam.x + SCREEN_WIDTH)
							Area3_Scene2_Enemy.erase(Area3_Scene2_Enemy.begin() + i);
					}
					break;
				case 8:
					if (sophia.x < 832) Area3_Scene2_Enemy[i].isDraw = true;
					if (Area3_Scene2_Enemy[i].isDraw == true)
					{
						Area3_Scene2_Enemy[i].x += 5;
						Area3_Scene2_Enemy[i].y = 560 + 48 * cos(float(Area3_Scene2_Enemy[i].x) / 32);
						if (Area3_Scene2_Enemy[i].x > cam.x + SCREEN_WIDTH)
							Area3_Scene2_Enemy.erase(Area3_Scene2_Enemy.begin() + i);
					}
					break;
				case 9:
					if (Area3_Scene2_Enemy[i].x <= 128)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 256)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 11:
					if (Area3_Scene2_Enemy[i].x <= 736)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 928)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 12:
					if (Area3_Scene2_Enemy[i].x <= 1088)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 1184)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 13:
					if (Area3_Scene2_Enemy[i].x <= 1248)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 1440)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 15:
					if (Area3_Scene2_Enemy[i].x <= 1376)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 1568)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 16:
					if (Area3_Scene2_Enemy[i].x <= 1760)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 1952)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 17:
					if (Area3_Scene2_Enemy[i].x <= 1824)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 2016)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 18:
					if (sophia.x > 1920 && sophia.y > 832) Area3_Scene2_Enemy[i].isDraw = true;
					if (Area3_Scene2_Enemy[i].isDraw == true)
					{
						Area3_Scene2_Enemy[i].x += 5;
						Area3_Scene2_Enemy[i].y = 816 + 48 * cos(float(Area3_Scene2_Enemy[i].x) / 32);
						if (Area3_Scene2_Enemy[i].x > cam.x + SCREEN_WIDTH)
							Area3_Scene2_Enemy.erase(Area3_Scene2_Enemy.begin() + i);
					}
					break;
				case 19:
					if (sophia.x > 1920 && sophia.y > 832) Area3_Scene2_Enemy[i].isDraw = true;
					if (Area3_Scene2_Enemy[i].isDraw == true)
					{
						Area3_Scene2_Enemy[i].x += 5;
						Area3_Scene2_Enemy[i].y = 816 + 48 * cos(float(Area3_Scene2_Enemy[i].x) / 32);
						if (Area3_Scene2_Enemy[i].x > cam.x + SCREEN_WIDTH)
							Area3_Scene2_Enemy.erase(Area3_Scene2_Enemy.begin() + i);
					}
					break;
				default:
					break;
				}
			}

#pragma endregion
		}
	}

#pragma region Draw

	if (d3ddev->BeginScene())
	{
		// Bắt đầu Sprite Handler
		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

		if (mapid == 3)
		{
#pragma region Draw Jason
			if (jason.hp > 0)
			{
				D3DXVECTOR3 position2((float)jason.x - cam.x, (float)jason.y - cam.y, 0);

				// player moving
				if (jason.movex != 0 || jason.movey != 0)
				{

					if (jason.direction == 6)
						sprite_handler->Draw(
							jason_image_right[jason.curframe],
							NULL,
							NULL,
							&position2,
							D3DCOLOR_XRGB(255, 255, 255));

					if (jason.direction == 4)
						sprite_handler->Draw(
							jason_image_left[jason.curframe],
							NULL,
							NULL,
							&position2,
							D3DCOLOR_XRGB(255, 255, 255));

					if (jason.direction == 8)
						sprite_handler->Draw(
							jason_image_up[jason.curframe],
							NULL,
							NULL,
							&position2,
							D3DCOLOR_XRGB(255, 255, 255));

					if (jason.direction == 2)
						sprite_handler->Draw(
							jason_image_down[jason.curframe],
							NULL,
							NULL,
							&position2,
							D3DCOLOR_XRGB(255, 255, 255));
				}
				else //player stop
				{
					if (jason.direction == 6)
						sprite_handler->Draw(
							jason_image_right[1],
							NULL,
							NULL,
							&position2,
							D3DCOLOR_XRGB(255, 255, 255));

					if (jason.direction == 4)
						sprite_handler->Draw(
							jason_image_left[1],
							NULL,
							NULL,
							&position2,
							D3DCOLOR_XRGB(255, 255, 255));

					if (jason.direction == 8)
						sprite_handler->Draw(
							jason_image_up[1],
							NULL,
							NULL,
							&position2,
							D3DCOLOR_XRGB(255, 255, 255));

					if (jason.direction == 2)
						sprite_handler->Draw(
							jason_image_down[1],
							NULL,
							NULL,
							&position2,
							D3DCOLOR_XRGB(255, 255, 255));
				}

				for (int i = 0; i < jason_bullet.size(); i++)
				{
					D3DXVECTOR3 positionbullet((float)jason_bullet[i].x - cam.x, (float)jason_bullet[i].y - cam.y, 0);
					sprite_handler->Draw(
						jason_bullet_image[jason_bullet[i].direction],
						NULL, NULL,
						&positionbullet,
						D3DCOLOR_XRGB(255, 255, 255));
				}

				for (int i = 0; i < explosion.size(); i++)
				{
					D3DXVECTOR3 positionexplosion((float)explosion[i].x - cam.x, (float)explosion[i].y - cam.y, 0);
					sprite_handler->Draw(
						dungeon_bullet_explosion_image[explosion[i].curframe],
						NULL, NULL,
						&positionexplosion,
						D3DCOLOR_XRGB(255, 255, 255));
				}

				D3DXVECTOR3 positionhpbar(16, 256, 0);
				sprite_handler->Draw(
					hp_bar_image[jason.hp],
					NULL, NULL,
					&positionhpbar,
					D3DCOLOR_XRGB(255, 255, 255));
			}
			else
			{
				for (int i = 0; i < jason_die.size(); i++)
				{
					D3DXVECTOR3 positiondie((float)jason_die[i].x - cam.x, (float)jason_die[i].y - cam.y, 0);
					sprite_handler->Draw(
						jason_die_image[jason_die[i].curframe],
						NULL, NULL,
						&positiondie,
						D3DCOLOR_XRGB(255, 255, 255));
				}
			}

			for (int i = 0; i < items_dungeon.size(); i++)
			{
				D3DXVECTOR3 positionitem((float)items_dungeon[i].x - cam.x, (float)items_dungeon[i].y - cam.y, 0);
				sprite_handler->Draw(
					P_item_image[0],
					NULL, NULL,
					&positionitem,
					D3DCOLOR_XRGB(255, 255, 255));
			}
#pragma endregion

#pragma region Draw Enemy Dungeon

			for (int i = 0; i < Dungeon_Enemy.size(); i++)
			{
				D3DXVECTOR3 position3((float)Dungeon_Enemy[i].x - cam.x, (float)Dungeon_Enemy[i].y - cam.y, 0);
				sprite_handler->Draw(
					Dungeon_Enemy[i].image[Dungeon_Enemy[i].curframe],
					NULL,
					NULL,
					&position3,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			for (int i = 0; i < dungeon_enemy_explosion.size(); i++)
			{
				D3DXVECTOR3 positionexplosion((float)dungeon_enemy_explosion[i].x - cam.x, (float)dungeon_enemy_explosion[i].y - cam.y, 0);
				sprite_handler->Draw(
					dungeon_enemy_explosion_image[dungeon_enemy_explosion[i].curframe],
					NULL, NULL,
					&positionexplosion,
					D3DCOLOR_XRGB(255, 255, 255));
			}

#pragma endregion


		}
		else if (mapid == 1 || mapid == 2)
		{
#pragma region Draw Sophia
			if (sophia.hp > 0)
			{
				D3DXVECTOR3 position1((float)sophia.body_x - cam.x, (float)sophia.body_y - cam.y, 0);
				D3DXVECTOR3 position2((float)sophia.wheelleft_x - cam.x, (float)sophia.wheelleft_y - cam.y, 0);
				D3DXVECTOR3 position3((float)sophia.wheelright_x - cam.x, (float)sophia.wheelright_y - cam.y, 0);
				D3DXVECTOR3 position4((float)sophia.midwheel_x - cam.x, (float)sophia.midwheel_y - cam.y, 0);
				D3DXVECTOR3 position5((float)sophia.gun_x - cam.x, (float)sophia.gun_y - cam.y, 0);

				if (sophia.direction == 68)
				{
					sprite_handler->Draw(
						sophia_body_image[5],
						NULL,
						NULL,
						&position1,
						D3DCOLOR_XRGB(255, 255, 255));

					sprite_handler->Draw(
						sophia_gun_image[2],
						NULL,
						NULL,
						&position5,
						D3DCOLOR_XRGB(255, 255, 255));
				}
				if (sophia.direction == 48)
				{
					sprite_handler->Draw(
						sophia_body_image[4],
						NULL,
						NULL,
						&position1,
						D3DCOLOR_XRGB(255, 255, 255));

					sprite_handler->Draw(
						sophia_gun_image[2],
						NULL,
						NULL,
						&position5,
						D3DCOLOR_XRGB(255, 255, 255));
				}
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
					sophia_wheel_image[sophia.wheelcurframe],
					NULL, NULL,
					&position2,
					D3DCOLOR_XRGB(255, 255, 255));
				sprite_handler->Draw(
					sophia_wheel_image[sophia.wheelcurframe],
					NULL, NULL,
					&position3,
					D3DCOLOR_XRGB(255, 255, 255));
				sprite_handler->Draw(
					sophia_mid_wheel_image,
					NULL, NULL,
					&position4,
					D3DCOLOR_XRGB(255, 255, 255));

				for (int i = 0; i < sophia_bullet.size(); i++)
				{
					D3DXVECTOR3 positionbullet((float)sophia_bullet[i].x - cam.x, (float)sophia_bullet[i].y - cam.y, 0);
					sprite_handler->Draw(
						sophia_bullet_image[sophia_bullet[i].direction],
						NULL, NULL,
						&positionbullet,
						D3DCOLOR_XRGB(255, 255, 255));
				}

				for (int i = 0; i < explosion.size(); i++)
				{
					D3DXVECTOR3 positionexplosion((float)explosion[i].x - cam.x, (float)explosion[i].y - cam.y, 0);
					sprite_handler->Draw(
						area3_bullet_explosion_image[explosion[i].curframe],
						NULL, NULL,
						&positionexplosion,
						D3DCOLOR_XRGB(255, 255, 255));
				}

				D3DXVECTOR3 positionhpbar(16, 256, 0);
				sprite_handler->Draw(
					hp_bar_image[sophia.hp],
					NULL, NULL,
					&positionhpbar,
					D3DCOLOR_XRGB(255, 255, 255));
			}
			else
			{
				for (int i = 0; i < sophia_explosion.size(); i++)
				{
					D3DXVECTOR3 positionexplosion((float)sophia_explosion[i].x - cam.x, (float)sophia_explosion[i].y - cam.y, 0);
					sprite_handler->Draw(
						sophia_explosion_image[sophia_explosion[i].curframe],
						NULL, NULL,
						&positionexplosion,
						D3DCOLOR_XRGB(255, 255, 255));
				}
			}

			// Draw item
			for (int i = 0; i < items_area3_scene1.size(); i++)
			{
				D3DXVECTOR3 positionitem((float)items_area3_scene1[i].x - cam.x, (float)items_area3_scene1[i].y - cam.y, 0);
				sprite_handler->Draw(
					P_item_image[0],
					NULL, NULL,
					&positionitem,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			for (int i = 0; i < items_area3_scene2.size(); i++)
			{
				D3DXVECTOR3 positionitem((float)items_area3_scene2[i].x - cam.x, (float)items_area3_scene2[i].y - cam.y, 0);
				sprite_handler->Draw(
					P_item_image[0],
					NULL, NULL,
					&positionitem,
					D3DCOLOR_XRGB(255, 255, 255));
			}

#pragma endregion
		}

		if (mapid == 1)
		{
#pragma region Draw Enemy Area3 Scene1

			for (int i = 0; i < Area3_Scene1_Enemy.size(); i++)
			{
				if (Area3_Scene1_Enemy[i].isDraw == true)
				{
					D3DXVECTOR3 position6((float)Area3_Scene1_Enemy[i].x - cam.x, (float)Area3_Scene1_Enemy[i].y - cam.y, 0);
					sprite_handler->Draw(
						Area3_Scene1_Enemy[i].image[Area3_Scene1_Enemy[i].curframe],
						NULL,
						NULL,
						&position6,
						D3DCOLOR_XRGB(255, 255, 255));
				}
			}

			for (int i = 0; i < enemy_drop_bullet.size(); i++)
			{
				D3DXVECTOR3 positionbullet((float)enemy_drop_bullet[i].x - cam.x, (float)enemy_drop_bullet[i].y - cam.y, 0);
				sprite_handler->Draw(
					enemy_drop_bullet_image[0],
					NULL,
					NULL,
					&positionbullet,
					D3DCOLOR_XRGB(255, 255, 255));
			}
#pragma endregion
		}
		else if (mapid == 2)
		{
#pragma region Draw Enemy Area3 Scene2
			for (int i = 0; i < Area3_Scene2_Enemy.size(); i++)
			{
				if (Area3_Scene2_Enemy[i].isDraw == true)
				{
					D3DXVECTOR3 position6((float)Area3_Scene2_Enemy[i].x - cam.x, (float)Area3_Scene2_Enemy[i].y - cam.y, 0);
					sprite_handler->Draw(
						Area3_Scene2_Enemy[i].image[Area3_Scene2_Enemy[i].curframe],
						NULL,
						NULL,
						&position6,
						D3DCOLOR_XRGB(255, 255, 255));
				}
			}
#pragma endregion
		}

#pragma region Draw Map

		int offset_y = cam.y % TILE_SIZE;
		int offset_x = cam.x % TILE_SIZE;

		RECT rect_des;
		rect_des.top = 0;
		rect_des.bottom = rect_des.top + TILE_SIZE - offset_y;
		rect_des.left = 0;
		rect_des.right = rect_des.left + TILE_SIZE - offset_x;

		RECT rect_src;
		rect_src.top = offset_y;
		rect_src.bottom = TILE_SIZE;
		rect_src.left = offset_x;
		rect_src.right = TILE_SIZE;

		// Draw first line
		int j;
		for (j = cam.x / TILE_SIZE; j < (SCREEN_WIDTH + cam.x) / TILE_SIZE; j++)
		{
			if (j != cam.x / TILE_SIZE)
			{
				rect_des.left = rect_des.right;
				rect_des.right = rect_des.left + TILE_SIZE;

				rect_src.left = 0;
				rect_src.right = TILE_SIZE;
			}

			d3ddev->StretchRect(map.image[map.matrix[cam.y / TILE_SIZE][j] - 1],
				&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);
		}
		// Draw last cell of line
		rect_des.left = rect_des.right;
		rect_des.right = rect_des.left + offset_x;

		rect_src.left = 0;
		rect_src.right = offset_x;

		d3ddev->StretchRect(map.image[map.matrix[cam.y / TILE_SIZE][j] - 1],
			&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);

		rect_src.top = 0;
		for (int i = cam.y / TILE_SIZE + 1; i < (SCREEN_HEIGHT + cam.y) / TILE_SIZE; i++)
		{
			rect_des.top = rect_des.bottom;
			rect_des.bottom = rect_des.top + TILE_SIZE;
			rect_des.left = 0;
			rect_des.right = rect_des.left + TILE_SIZE - offset_x;

			rect_src.left = offset_x;
			rect_src.right = TILE_SIZE;
			for (j = cam.x / TILE_SIZE; j < (SCREEN_WIDTH + cam.x) / TILE_SIZE; j++)
			{
				if (j != cam.x / TILE_SIZE)
				{
					rect_des.left = rect_des.right;
					rect_des.right = rect_des.left + TILE_SIZE;

					rect_src.left = 0;
					rect_src.right = TILE_SIZE;
				}

				d3ddev->StretchRect(map.image[map.matrix[i][j] - 1],
					&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);
			}

			rect_des.left = rect_des.right;
			rect_des.right = rect_des.left + offset_x;

			rect_src.left = 0;
			rect_src.right = offset_x;

			d3ddev->StretchRect(map.image[map.matrix[i][j] - 1],
				&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);
		}

		rect_src.top = 0;
		rect_src.bottom = offset_y;
		rect_src.left = offset_x;
		rect_src.right = TILE_SIZE;

		rect_des.top = rect_des.bottom;
		rect_des.bottom = rect_des.top + offset_y;
		rect_des.left = 0;
		rect_des.right = rect_des.left + TILE_SIZE - offset_x;

		for (j = cam.x / TILE_SIZE; j < (SCREEN_WIDTH + cam.x) / TILE_SIZE; j++)
		{
			if (j != cam.x / TILE_SIZE)
			{
				rect_des.left = rect_des.right;
				rect_des.right = rect_des.left + TILE_SIZE;

				rect_src.left = 0;
				rect_src.right = TILE_SIZE;
			}

			d3ddev->StretchRect(map.image[map.matrix[(SCREEN_HEIGHT + cam.y) / TILE_SIZE][j] - 1],
				&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);
		}

		rect_des.left = rect_des.right;
		rect_des.right = rect_des.left + offset_x;

		rect_src.left = 0;
		rect_src.right = offset_x;

		d3ddev->StretchRect(map.image[map.matrix[(SCREEN_HEIGHT + cam.y) / TILE_SIZE][j] - 1],
			&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);
#pragma endregion

#pragma region Map cover player

		if (mapid == 1)
		{
			//
		}
		else if (mapid == 2)
		{
			//
		}
		else if (mapid == 3)
		{
			for (int i = 0; i < 4; i++)
			{
				D3DXVECTOR3 positiontile1((float)32 * 6 - cam.x, (float)32 * arr[i] - cam.y, 0);
				sprite_handler->Draw(
					tilemap8,
					NULL, NULL,
					&positiontile1,
					D3DCOLOR_XRGB(255, 255, 255));

				D3DXVECTOR3 positiontile2((float)32 * 6 - cam.x, (float)32 * (arr[i] + 1) - cam.y, 0);
				sprite_handler->Draw(
					tilemap20,
					NULL, NULL,
					&positiontile2,
					D3DCOLOR_XRGB(255, 255, 255));

				for (int j = 7; j < 14; j++)
				{
					D3DXVECTOR3 positiontile3((float)32 * j - cam.x, (float)32 * arr[i] - cam.y, 0);
					sprite_handler->Draw(
						tilemap9,
						NULL, NULL,
						&positiontile3,
						D3DCOLOR_XRGB(255, 255, 255));

					D3DXVECTOR3 positiontile4((float)32 * j - cam.x, (float)32 * (arr[i] + 1) - cam.y, 0);
					sprite_handler->Draw(
						tilemap21,
						NULL, NULL,
						&positiontile4,
						D3DCOLOR_XRGB(255, 255, 255));
				}


			}

			for (int i = 0; i < 3; i++)
			{
				D3DXVECTOR3 positiontile1((float)32 * 9 - cam.x, (float)32 * brr[i] - cam.y, 0);
				sprite_handler->Draw(
					tilemap10,
					NULL, NULL,
					&positiontile1,
					D3DCOLOR_XRGB(255, 255, 255));

				D3DXVECTOR3 positiontile2((float)32 * 9 - cam.x, (float)32 * (brr[i] + 1) - cam.y, 0);
				sprite_handler->Draw(
					tilemap22,
					NULL, NULL,
					&positiontile2,
					D3DCOLOR_XRGB(255, 255, 255));

				for (int j = 2; j < 9; j++)
				{
					D3DXVECTOR3 positiontile3((float)32 * j - cam.x, (float)32 * brr[i] - cam.y, 0);
					sprite_handler->Draw(
						tilemap9,
						NULL, NULL,
						&positiontile3,
						D3DCOLOR_XRGB(255, 255, 255));
					D3DXVECTOR3 positiontile4((float)32 * j - cam.x, (float)32 * (brr[i] + 1) - cam.y, 0);
					sprite_handler->Draw(
						tilemap21,
						NULL, NULL,
						&positiontile4,
						D3DCOLOR_XRGB(255, 255, 255));
				}
			}

			D3DXVECTOR3 positiontile1((float)32 * 5 - cam.x, (float)32 * 44 - cam.y, 0);
			sprite_handler->Draw(
				tilemap10,
				NULL, NULL,
				&positiontile1,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile2((float)32 * 5 - cam.x, (float)32 * 45 - cam.y, 0);
			sprite_handler->Draw(
				tilemap22,
				NULL, NULL,
				&positiontile2,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile3((float)32 * 10 - cam.x, (float)32 * 44 - cam.y, 0);
			sprite_handler->Draw(
				tilemap8,
				NULL, NULL,
				&positiontile3,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile4((float)32 * 10 - cam.x, (float)32 * 45 - cam.y, 0);
			sprite_handler->Draw(
				tilemap20,
				NULL, NULL,
				&positiontile4,
				D3DCOLOR_XRGB(255, 255, 255));

			for (int i = 2; i < 5; i++)
			{
				D3DXVECTOR3 positiontile5((float)32 * i - cam.x, (float)32 * 44 - cam.y, 0);
				sprite_handler->Draw(
					tilemap9,
					NULL, NULL,
					&positiontile5,
					D3DCOLOR_XRGB(255, 255, 255));

				D3DXVECTOR3 positiontile6((float)32 * i - cam.x, (float)32 * 45 - cam.y, 0);
				sprite_handler->Draw(
					tilemap21,
					NULL, NULL,
					&positiontile6,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			for (int i = 11; i < 14; i++)
			{
				D3DXVECTOR3 positiontile5((float)32 * i - cam.x, (float)32 * 44 - cam.y, 0);
				sprite_handler->Draw(
					tilemap9,
					NULL, NULL,
					&positiontile5,
					D3DCOLOR_XRGB(255, 255, 255));

				D3DXVECTOR3 positiontile6((float)32 * i - cam.x, (float)32 * 45 - cam.y, 0);
				sprite_handler->Draw(
					tilemap21,
					NULL, NULL,
					&positiontile6,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			D3DXVECTOR3 positiontile7((float)32 * 6 - cam.x, (float)32 * 108 - cam.y, 0);
			sprite_handler->Draw(
				tilemap10,
				NULL, NULL,
				&positiontile7,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile8((float)32 * 6 - cam.x, (float)32 * 109 - cam.y, 0);
			sprite_handler->Draw(
				tilemap22,
				NULL, NULL,
				&positiontile8,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile9((float)32 * 9 - cam.x, (float)32 * 108 - cam.y, 0);
			sprite_handler->Draw(
				tilemap8,
				NULL, NULL,
				&positiontile9,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile10((float)32 * 9 - cam.x, (float)32 * 109 - cam.y, 0);
			sprite_handler->Draw(
				tilemap20,
				NULL, NULL,
				&positiontile10,
				D3DCOLOR_XRGB(255, 255, 255));

			for (int i = 2; i < 6; i++)
			{
				D3DXVECTOR3 positiontile5((float)32 * i - cam.x, (float)32 * 108 - cam.y, 0);
				sprite_handler->Draw(
					tilemap9,
					NULL, NULL,
					&positiontile5,
					D3DCOLOR_XRGB(255, 255, 255));

				D3DXVECTOR3 positiontile6((float)32 * i - cam.x, (float)32 * 109 - cam.y, 0);
				sprite_handler->Draw(
					tilemap21,
					NULL, NULL,
					&positiontile6,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			for (int i = 10; i < 14; i++)
			{
				D3DXVECTOR3 positiontile5((float)32 * i - cam.x, (float)32 * 108 - cam.y, 0);
				sprite_handler->Draw(
					tilemap9,
					NULL, NULL,
					&positiontile5,
					D3DCOLOR_XRGB(255, 255, 255));

				D3DXVECTOR3 positiontile6((float)32 * i - cam.x, (float)32 * 109 - cam.y, 0);
				sprite_handler->Draw(
					tilemap21,
					NULL, NULL,
					&positiontile6,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			D3DXVECTOR3 positiontile11((float)32 * 7 - cam.x, (float)32 * 108 - cam.y, 0);
			sprite_handler->Draw(
				tilemap11,
				NULL, NULL,
				&positiontile11,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile12((float)32 * 8 - cam.x, (float)32 * 108 - cam.y, 0);
			sprite_handler->Draw(
				tilemap12,
				NULL, NULL,
				&positiontile12,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile13((float)32 * 7 - cam.x, (float)32 * 109 - cam.y, 0);
			sprite_handler->Draw(
				tilemap23,
				NULL, NULL,
				&positiontile13,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile14((float)32 * 8 - cam.x, (float)32 * 109 - cam.y, 0);
			sprite_handler->Draw(
				tilemap24,
				NULL, NULL,
				&positiontile14,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile15((float)32 * 7 - cam.x, (float)32 * 110 - cam.y, 0);
			sprite_handler->Draw(
				tilemap35,
				NULL, NULL,
				&positiontile15,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile16((float)32 * 8 - cam.x, (float)32 * 110 - cam.y, 0);
			sprite_handler->Draw(
				tilemap36,
				NULL, NULL,
				&positiontile16,
				D3DCOLOR_XRGB(255, 255, 255));

			for (int i = 2; i < 30; i++)
			{
				D3DXVECTOR3 positiontile5((float)32 * i - cam.x, (float)32 * 123 - cam.y, 0);
				sprite_handler->Draw(
					tilemap9,
					NULL, NULL,
					&positiontile5,
					D3DCOLOR_XRGB(255, 255, 255));

				D3DXVECTOR3 positiontile6((float)32 * i - cam.x, (float)32 * 124 - cam.y, 0);
				sprite_handler->Draw(
					tilemap21,
					NULL, NULL,
					&positiontile6,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			D3DXVECTOR3 positiontile17((float)32 * 23 - cam.x, (float)32 * 108 - cam.y, 0);
			sprite_handler->Draw(
				tilemap11,
				NULL, NULL,
				&positiontile17,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile18((float)32 * 24 - cam.x, (float)32 * 108 - cam.y, 0);
			sprite_handler->Draw(
				tilemap12,
				NULL, NULL,
				&positiontile18,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile19((float)32 * 23 - cam.x, (float)32 * 109 - cam.y, 0);
			sprite_handler->Draw(
				tilemap23,
				NULL, NULL,
				&positiontile19,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile20((float)32 * 24 - cam.x, (float)32 * 109 - cam.y, 0);
			sprite_handler->Draw(
				tilemap24,
				NULL, NULL,
				&positiontile20,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile21((float)32 * 23 - cam.x, (float)32 * 110 - cam.y, 0);
			sprite_handler->Draw(
				tilemap35,
				NULL, NULL,
				&positiontile21,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile22((float)32 * 24 - cam.x, (float)32 * 110 - cam.y, 0);
			sprite_handler->Draw(
				tilemap36,
				NULL, NULL,
				&positiontile22,
				D3DCOLOR_XRGB(255, 255, 255));
		
			D3DXVECTOR3 positiontile23((float)32 * 22 - cam.x, (float)32 * 108 - cam.y, 0);
			sprite_handler->Draw(
				tilemap10,
				NULL, NULL,
				&positiontile23,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile24((float)32 * 22 - cam.x, (float)32 * 109 - cam.y, 0);
			sprite_handler->Draw(
				tilemap22,
				NULL, NULL,
				&positiontile24,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile25((float)32 * 25 - cam.x, (float)32 * 108 - cam.y, 0);
			sprite_handler->Draw(
				tilemap8,
				NULL, NULL,
				&positiontile25,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile26((float)32 * 25 - cam.x, (float)32 * 109 - cam.y, 0);
			sprite_handler->Draw(
				tilemap20,
				NULL, NULL,
				&positiontile26,
				D3DCOLOR_XRGB(255, 255, 255));

			for (int i = 18; i < 22; i++)
			{
				D3DXVECTOR3 positiontile5((float)32 * i - cam.x, (float)32 * 108 - cam.y, 0);
				sprite_handler->Draw(
					tilemap9,
					NULL, NULL,
					&positiontile5,
					D3DCOLOR_XRGB(255, 255, 255));

				D3DXVECTOR3 positiontile6((float)32 * i - cam.x, (float)32 * 109 - cam.y, 0);
				sprite_handler->Draw(
					tilemap21,
					NULL, NULL,
					&positiontile6,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			for (int i = 26; i < 30; i++)
			{
				D3DXVECTOR3 positiontile5((float)32 * i - cam.x, (float)32 * 108 - cam.y, 0);
				sprite_handler->Draw(
					tilemap9,
					NULL, NULL,
					&positiontile5,
					D3DCOLOR_XRGB(255, 255, 255));

				D3DXVECTOR3 positiontile6((float)32 * i - cam.x, (float)32 * 109 - cam.y, 0);
				sprite_handler->Draw(
					tilemap21,
					NULL, NULL,
					&positiontile6,
					D3DCOLOR_XRGB(255, 255, 255));
			}
		}

#pragma endregion

		sprite_handler->End();
		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
#pragma endregion

	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);
}

void Game_End(HWND hwnd)
{
	int n;
	for (n = 0; n < 3; n++)
		if (jason_image_right[n] != NULL)
			jason_image_right[n]->Release();

	if (sprite_handler != NULL)
		sprite_handler->Release();
}
