#include "game.h"

LPD3DXSPRITE sprite_handler;
HRESULT result;

// Items
LPDIRECT3DTEXTURE9 P_item_image[1];
vector<SPRITE> items_area3_scene1, items_area3_scene2, items_dungeon;

// Jason
SPRITE jason;
LPDIRECT3DTEXTURE9 jason_image_right[3], jason_image_left[3], jason_image_up[3], jason_image_down[3],
jason_bullet_image[4], jason_die_image[5];
vector<BULLET> jason_bullet;
LPDIRECT3DTEXTURE9 dungeon_bullet_explosion_image[2];
vector<SPRITE> jason_die;

// Sophia
SOPHIA sophia;
LPDIRECT3DTEXTURE9 sophia_wheel_image[4], sophia_mid_wheel_image, sophia_body_image[6], sophia_gun_image[5],
sophia_bullet_image[3], sophia_explosion_image[2];
vector<BULLET> sophia_bullet;
vector<SPRITE> sophia_explosion;
LPDIRECT3DTEXTURE9 area3_bullet_explosion_image[4];

LPDIRECT3DTEXTURE9 hp_bar_image[9];

vector<SPRITE> explosion;

// Small jason
SOPHIA small_jason;
LPDIRECT3DTEXTURE9 small_jason_image_left[4],
small_jason_image_right[4];

// Enemy in dungeon
LPDIRECT3DTEXTURE9 enemy_bug_gray_image[3],
enemy_bug_red_image[3],
enemy_cam_gray_image[2],
enemy_eye_gray_image[4];

LPDIRECT3DTEXTURE9 dungeon_enemy_explosion_image[2];
vector<SPRITE> dungeon_enemy_explosion;

LPDIRECT3DTEXTURE9 enemy_bug_bullet_image[1];
vector<BULLET> enemy_bug_bullet;
LPDIRECT3DTEXTURE9 enemy_cam_bullet_image[1];
vector<BULLET> enemy_cam_bullet;

// Enemy in Area3
LPDIRECT3DTEXTURE9 enemy_ball_left_gray_image[3], enemy_ball_right_gray_image[3],
enemy_globular_gray_image[5],
enemy_teeth_left_gray_image[4], enemy_teeth_right_gray_image[4];
LPDIRECT3DTEXTURE9 enemy_drop_red_image[2];
LPDIRECT3DTEXTURE9 enemy_drop_bullet_image[1];
vector<SPRITE> enemy_drop_bullet;

LPDIRECT3DTEXTURE9 enemy_rocket_gray_image[2];

vector<SPRITE> Dungeon_Enemy, Area3_Scene1_Enemy, Area3_Scene2_Enemy;
SPRITE temp;

// Map
MAP map_info;
MAP map_area3_scene1, map_area3_scene2, map_area3_scene3, map_dungeon;
int mapid; // 1: area3_scene1, 2: area3_scene2, 3: dungeon, 4: area3_scene3

LPDIRECT3DTEXTURE9 tilemap8, tilemap9, tilemap20, tilemap21,
tilemap10, tilemap22, tilemap11, tilemap12,
tilemap23, tilemap24, tilemap35, tilemap36;

LPDIRECT3DTEXTURE9 gate20, gate28, gate19, gate27,
gate18, gate26;

int arr[] = { 12,28,76,100 };
int brr[] = { 20,60,92 };

CAM cam;

// Some support variable
long start = GetTickCount();
long char_start_shoot = GetTickCount();
long char_start_get_hit = GetTickCount();
long enemy_start_get_hit = GetTickCount();
long enemy_start_shoot = GetTickCount();

bool flag = 1; // used for jason bullet
int player; // 0:small jason, 1:sophia, 2:jason, 

GSound* area3_sound, * switch_scene_sound;

GSound* sophia_shoot_sound, * sophia_bullet_explosion_sound,
* sophia_die_sound, * sophia_got_hit_sound, * sophia_jump_sound,
* swap_player_sound, * get_item_sound;

GSound* big_jason_shoot_sound, * big_jason_got_hit_sound,
* small_jason_jump_sound;

GSound* enemy_got_hit_sound, * enemy_die_sound,
* teeth_arrive_sound, * enemy_bug_shoot_sound, * enemy_cam_shoot_sound;

int Game_Init(HWND hwnd)
{
	srand(time(NULL));
	char s[100];

	result = D3DXCreateSprite(d3ddev, &sprite_handler);
	if (result != D3D_OK)
		return 0;

#pragma region Sound
	GSoundManager* dsound = new GSoundManager();
	dsound->Initialize(hwnd, DSSCL_PRIORITY);

	result = dsound->SetPrimaryBufferFormat(2, 22050, 16);

	sprintf_s(s, "Sound\\sophia_shoot.wav");
	result = dsound->Create(&sophia_shoot_sound, s);
	sprintf_s(s, "Sound\\area3_sound.wav");
	result = dsound->Create(&area3_sound, s);
	sprintf_s(s, "Sound\\sophia_bullet_explosion.wav");
	result = dsound->Create(&sophia_bullet_explosion_sound, s);
	sprintf_s(s, "Sound\\sophia_die.wav");
	result = dsound->Create(&sophia_die_sound, s);
	sprintf_s(s, "Sound\\sophia_got_hit.wav");
	result = dsound->Create(&sophia_got_hit_sound, s);
	sprintf_s(s, "Sound\\sophia_jump.wav");
	result = dsound->Create(&sophia_jump_sound, s);
	sprintf_s(s, "Sound\\swap_player.wav");
	result = dsound->Create(&swap_player_sound, s);
	sprintf_s(s, "Sound\\get_item.wav");
	result = dsound->Create(&get_item_sound, s);
	sprintf_s(s, "Sound\\big_jason_shoot.wav");
	result = dsound->Create(&big_jason_shoot_sound, s);
	sprintf_s(s, "Sound\\big_jason_got_hit.wav");
	result = dsound->Create(&big_jason_got_hit_sound, s);
	sprintf_s(s, "Sound\\small_jason_jump.wav");
	result = dsound->Create(&small_jason_jump_sound, s);
	sprintf_s(s, "Sound\\enemy_got_hit.wav");
	result = dsound->Create(&enemy_got_hit_sound, s);
	sprintf_s(s, "Sound\\enemy_die.wav");
	result = dsound->Create(&enemy_die_sound, s);
	sprintf_s(s, "Sound\\teeth_arrive.wav");
	result = dsound->Create(&teeth_arrive_sound, s);
	sprintf_s(s, "Sound\\switch_scene.wav");
	result = dsound->Create(&switch_scene_sound, s);

	sprintf_s(s, "Sound\\enemy_bug_shoot.wav");
	result = dsound->Create(&enemy_bug_shoot_sound, s);
	sprintf_s(s, "Sound\\enemy_cam_shoot.wav");
	result = dsound->Create(&enemy_cam_shoot_sound, s);

#pragma endregion

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

#pragma region Load Small Jason Image
	//
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(s, "Picture\\Small Jason\\small_jason_right_%d.png", i + 1);
		small_jason_image_right[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (small_jason_image_right[i] == NULL)
			return 0;

		sprintf_s(s, "Picture\\Small Jason\\small_jason_left_%d.png", i + 1);
		small_jason_image_left[i] = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
		if (small_jason_image_left[i] == NULL)
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

	for (int i = 0; i < 112; i++)
	{
		sprintf_s(s, "Picture\\Area3 tile set\\Area3_%d.png", i + 1);
		map_area3_scene3.image[i] = LoadSurface(s, NULL);
	}
	map_area3_scene3.height = 16 * 32;
	map_area3_scene3.width = 16 * 32;
	ifstream ifs3("Area3_Scene3.txt");
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int num;
			ifs3 >> num;
			map_area3_scene3.matrix[i][j] = num;
		}
	}
	ifs3.close();

	// Dungeon
	for (int i = 0; i < 78; i++)
	{
		sprintf_s(s, "Picture\\Dungeon tile set\\Dungeon%d.png", i + 1);
		map_dungeon.image[i] = LoadSurface(s, NULL);
	}
	sprintf_s(s, "Picture\\BreakableBlock\\BreakableGreen.png");
	map_dungeon.image[78] = LoadSurface(s, NULL);

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

	sprintf_s(s, "Picture\\Area3 tile set\\Area3_20.png");
	gate20 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Area3 tile set\\Area3_28.png");
	gate28 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Area3 tile set\\Area3_19.png");
	gate19 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Area3 tile set\\Area3_27.png");
	gate27 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Area3 tile set\\Area3_18.png");
	gate18 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
	sprintf_s(s, "Picture\\Area3 tile set\\Area3_26.png");
	gate26 = LoadTexture(s, D3DCOLOR_XRGB(0, 57, 115));
#pragma endregion

#pragma region Load Enemy Image

	for (int i = 0; i < 3; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\bug%d.png", i + 1);
		enemy_bug_gray_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (enemy_bug_gray_image[i] == NULL)
			return 0;
	}
	sprintf_s(s, "Picture\\Bullet\\enemy_bug_bullet.png");
	enemy_bug_bullet_image[0] = LoadTexture(s, D3DCOLOR_XRGB(0, 0, 255));
	if (enemy_bug_bullet_image[0] == NULL)
		return 0;

	sprintf_s(s, "Picture\\Bullet\\enemy_cam_bullet.png");
	enemy_cam_bullet_image[0] = LoadTexture(s, D3DCOLOR_XRGB(0, 0, 255));
	if (enemy_cam_bullet_image[0] == NULL)
		return 0;

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

	for (int i = 0; i < 4; i++)
	{
		sprintf_s(s, "Picture\\Enemy\\enemy_eye_%d.png", i + 1);
		enemy_eye_gray_image[i] = LoadTexture(s, D3DCOLOR_XRGB(255, 0, 255));
		if (enemy_eye_gray_image[i] == NULL)
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
	map_info = map_dungeon;
	mapid = 3;

	cam.x = 0;
	cam.y = 32;

	/*player = 1;*/
	player = 2;

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
	temp.x = 2048;
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

	temp.id = 15;
	temp.x = 416;
	temp.y = 3648;
	temp.width = 36;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 3;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_eye_gray_image[0];
	temp.image[1] = enemy_eye_gray_image[1];
	temp.image[2] = enemy_eye_gray_image[2];
	temp.image[3] = enemy_eye_gray_image[3];
	temp.movex = 0;
	Dungeon_Enemy.push_back(temp);

	temp.id = 16;
	temp.x = 192;
	temp.y = 3840;
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

	temp.id = 17;
	temp.x = 288;
	temp.y = 3840;
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

	temp.id = 18;
	temp.x = 640;
	temp.y = 3840;
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

	temp.id = 19;
	temp.x = 864;
	temp.y = 3808;
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

	temp.id = 20;
	temp.x = 896;
	temp.y = 3904;
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

	temp.id = 21;
	temp.x = 576;
	temp.y = 3616;
	temp.width = 34;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 1;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_cam_gray_image[0];
	temp.image[1] = enemy_cam_gray_image[1];
	temp.movex = 2;
	Dungeon_Enemy.push_back(temp);

	temp.id = 22;
	temp.x = 672;
	temp.y = 3648;
	temp.width = 34;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 1;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_cam_gray_image[0];
	temp.image[1] = enemy_cam_gray_image[1];
	temp.movex = 2;
	Dungeon_Enemy.push_back(temp);

	temp.id = 23;
	temp.x = 896;
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

	temp.id = 24;
	temp.x = 576;
	temp.y = 3296;
	temp.width = 36;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 3;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_eye_gray_image[0];
	temp.image[1] = enemy_eye_gray_image[1];
	temp.image[2] = enemy_eye_gray_image[2];
	temp.image[3] = enemy_eye_gray_image[3];
	temp.movex = 0;
	Dungeon_Enemy.push_back(temp);

	temp.id = 25;
	temp.x = 928;
	temp.y = 3168;
	temp.width = 36;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 3;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_eye_gray_image[0];
	temp.image[1] = enemy_eye_gray_image[1];
	temp.image[2] = enemy_eye_gray_image[2];
	temp.image[3] = enemy_eye_gray_image[3];
	temp.movex = 0;
	Dungeon_Enemy.push_back(temp);

	temp.id = 26;
	temp.x = 576;
	temp.y = 3040;
	temp.width = 36;
	temp.height = 36;
	temp.curframe = 0;
	temp.lastframe = 3;
	temp.animdelay = 5;
	temp.animcount = 0;
	temp.image[0] = enemy_eye_gray_image[0];
	temp.image[1] = enemy_eye_gray_image[1];
	temp.image[2] = enemy_eye_gray_image[2];
	temp.image[3] = enemy_eye_gray_image[3];
	temp.movex = 0;
	Dungeon_Enemy.push_back(temp);

	temp.id = 27;
	temp.x = 896;
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

#pragma endregion

#pragma endregion

	return 1;
}

void Game_Run(HWND hwnd)
{
	if (d3ddev == NULL)
		return;

	if (sophia.hp > 0)
		area3_sound->Play(0, DSBPLAY_LOOPING);
	else
		area3_sound->Stop();

	if (GetTickCount() - start >= 30)
	{
		// Tái lập lại thời gian
		start = GetTickCount();

		if (mapid == 3)
		{
#pragma region Update Jason, and Cam
			// jason alive
			if (jason.hp > 0)
			{
				// bullet moving (cos)
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
						if (GetTickCount() - char_start_shoot >= 100)
						{
							big_jason_shoot_sound->Reset();
							big_jason_shoot_sound->Play();

							// Tái lập lại thời gian
							char_start_shoot = GetTickCount();
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
					if (!map_info.jason_collide_left(jason))
					{
						jason.x += jason.movex;
						if (jason.x - cam.x - 32 < SCREEN_HEIGHT / 2 && cam.x > 0 && cam.y >= 3520)
							cam.x += jason.movex;
					}
				}
				else if (KEY_DOWN(VK_RIGHT))
				{
					jason.move_right();
					if (!map_info.jason_collide_right(jason))
					{
						jason.x += jason.movex;
						if (jason.x - cam.x - 32 > SCREEN_HEIGHT / 2 && jason.x < 768 && cam.y >= 3520)
							cam.x += jason.movex;
					}
				}
				else if (KEY_DOWN(VK_UP))
				{
					jason.move_up();
					if (!map_info.jason_collide_up(jason))
					{
						jason.y += jason.movey;
						if (cam.y >= 16 && (jason.y - cam.y) < SCREEN_HEIGHT / 2)
							cam.y += jason.movey;
					}
				}
				else if (KEY_DOWN(VK_DOWN))
				{
					jason.move_down();
					if (!map_info.jason_collide_down(jason))
					{
						jason.y += jason.movey;
						if (cam.y < map_info.height - SCREEN_HEIGHT - 32 && (jason.y - cam.y) > SCREEN_HEIGHT / 2)
							cam.y += jason.movey;
					}
				}
				else
				{
					jason.movex = 0;
					jason.movey = 0;
				}

				// Jason collide with trap
				if (map_info.jason_collide_trap_down(jason) ||
					map_info.jason_collide_trap_right(jason) ||
					map_info.jason_collide_trap_left(jason) ||
					map_info.jason_collide_trap_up(jason))
				{
					if (GetTickCount() - char_start_get_hit >= 500)
					{
						char_start_get_hit = GetTickCount();
						jason.hp -= 1;

						big_jason_got_hit_sound->Reset();
						big_jason_got_hit_sound->Play();
					}
				}

				// bullet collide with map, and explosion
				for (int i = 0; i < jason_bullet.size(); i++)
				{
					if (jason_bullet[i].x < cam.x || jason_bullet[i].x > cam.x + SCREEN_WIDTH ||
						jason_bullet[i].y < cam.y || jason_bullet[i].y > cam.y + SCREEN_HEIGHT)
						jason_bullet.erase(jason_bullet.begin() + i);

					else if (map_info.jason_bullet_collide_right(jason_bullet[i]) ||
						map_info.jason_bullet_collide_left(jason_bullet[i]) ||
						map_info.jason_bullet_collide_up(jason_bullet[i]) ||
						map_info.jason_bullet_collide_down(jason_bullet[i]))
					{
						SPRITE ex_temp;
						ex_temp.x = jason_bullet[i].x;
						ex_temp.y = jason_bullet[i].y;
						ex_temp.curframe = 0;
						ex_temp.lastframe = 1;
						ex_temp.animcount = 0;
						ex_temp.animdelay = 2;
						explosion.push_back(ex_temp);

						sophia_bullet_explosion_sound->Reset();
						sophia_bullet_explosion_sound->Play();
					}
				}

				// update jason frame
				if (++jason.animcount > jason.animdelay)
				{
					jason.animcount = 0;
					if (++jason.curframe > jason.lastframe)
						jason.curframe = 0;
				}

				// update exploseion frame
				for (int i = 0; i < explosion.size(); i++)
				{
					if (++explosion[i].animcount > explosion[i].animdelay)
					{
						explosion[i].animcount = 0;
						if (++explosion[i].curframe > explosion[i].lastframe)
							explosion.erase(explosion.begin() + i);
					}
				}

				// jason get an item
				for (int i = 0; i < items_dungeon.size(); i++)
				{
					if (items_dungeon[i].Jason_collide(jason))
					{
						items_dungeon.erase(items_dungeon.begin() + i);
						if (jason.hp < 8)
							jason.hp += 1;

						get_item_sound->Reset();
						get_item_sound->Play();
					}
				}
			}
			// jason die
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

					big_jason_got_hit_sound->Reset();
					big_jason_got_hit_sound->Play();
				}

				// enemy get hit by bullet
				for (int j = 0; j < jason_bullet.size(); j++)
				{
					if (Dungeon_Enemy[i].Bullet_collide(jason_bullet[j]) && GetTickCount() - enemy_start_get_hit >= 30)
					{
						enemy_start_get_hit = GetTickCount();
						Dungeon_Enemy[i].hp--;

						enemy_got_hit_sound->Reset();
						enemy_got_hit_sound->Play();

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

							enemy_die_sound->Reset();
							enemy_die_sound->Play();
						}
						jason_bullet.erase(jason_bullet.begin() + j);
						break;
					}
				}
			}

			for (int i = 0; i < Dungeon_Enemy.size(); i++)
			{
				// update enemy frame
				if (++Dungeon_Enemy[i].animcount > Dungeon_Enemy[i].animdelay)
				{
					Dungeon_Enemy[i].animcount = 0;
					if (++Dungeon_Enemy[i].curframe > Dungeon_Enemy[i].lastframe)
						Dungeon_Enemy[i].curframe = 0;
				}

				// Enemy behaviour
				if (Dungeon_Enemy[i].id <= 14 || (Dungeon_Enemy[i].id >= 16 && Dungeon_Enemy[i].id <= 20))
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
							if (!map_info.jason_collide_right(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].x += Dungeon_Enemy[i].movex;
						}
						else if (Dungeon_Enemy[i].movex < 0)
						{
							if (!map_info.jason_collide_left(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].x += Dungeon_Enemy[i].movex;
						}

						if (Dungeon_Enemy[i].movey > 0)
						{
							if (!map_info.jason_collide_down(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].y += Dungeon_Enemy[i].movey;
						}
						else if (Dungeon_Enemy[i].movey < 0)
						{
							if (!map_info.jason_collide_up(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].y += Dungeon_Enemy[i].movey;
						}
					}
				}

				if (Dungeon_Enemy[i].id == 15)
				{
					if (jason.y + jason.height >= Dungeon_Enemy[i].y)
					{
						Dungeon_Enemy[i].movex = -8;
					}
					if (Dungeon_Enemy[i].x <= 64)
						Dungeon_Enemy[i].movex = 0;
					Dungeon_Enemy[i].x += Dungeon_Enemy[i].movex;
				}

				if (Dungeon_Enemy[i].id == 21 || Dungeon_Enemy[i].id == 22)
				{
					if (Dungeon_Enemy[i].x <= 592)
						Dungeon_Enemy[i].movex = 2;
					else if (Dungeon_Enemy[i].x >= 912)
						Dungeon_Enemy[i].movex = -2;
					Dungeon_Enemy[i].x += Dungeon_Enemy[i].movex;
				}

				if ((Dungeon_Enemy[i].id == 23 && jason.y <= 3456) || Dungeon_Enemy[i].id == 27)
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
							if (!map_info.jason_collide_right(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].x += Dungeon_Enemy[i].movex;
						}
						else if (Dungeon_Enemy[i].movex < 0)
						{
							if (!map_info.jason_collide_left(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].x += Dungeon_Enemy[i].movex;
						}

						if (Dungeon_Enemy[i].movey > 0)
						{
							if (!map_info.jason_collide_down(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].y += Dungeon_Enemy[i].movey;
						}
						else if (Dungeon_Enemy[i].movey < 0)
						{
							if (!map_info.jason_collide_up(Dungeon_Enemy[i]))
								Dungeon_Enemy[i].y += Dungeon_Enemy[i].movey;
						}
					}
				}

				if (Dungeon_Enemy[i].id == 24 || Dungeon_Enemy[i].id == 26)
				{
					if (jason.x >= 576)
					{
						if (jason.y <= Dungeon_Enemy[i].y)
						{
							Dungeon_Enemy[i].movex = 8;
						}
						if (Dungeon_Enemy[i].x >= 924)
							Dungeon_Enemy[i].movex = 0;
						Dungeon_Enemy[i].x += Dungeon_Enemy[i].movex;
					}
				}

				if (Dungeon_Enemy[i].id == 25)
				{
					if (jason.x >= 576)
					{
						if (jason.y <= Dungeon_Enemy[i].y)
						{
							Dungeon_Enemy[i].movex = -8;
						}
						if (Dungeon_Enemy[i].x <= 576)
							Dungeon_Enemy[i].movex = 0;
						Dungeon_Enemy[i].x += Dungeon_Enemy[i].movex;
					}
				}

				// update enemy bullet
				for (int i = 0; i < enemy_bug_bullet.size(); i++)
				{
					enemy_bug_bullet[i].x += enemy_bug_bullet[i].movex;
					enemy_bug_bullet[i].y += enemy_bug_bullet[i].movey;

					// enemy bullet hit jason
					if (jason.Bullet_collide(enemy_bug_bullet[i]) && GetTickCount() - char_start_get_hit >= 1000)
					{
						char_start_get_hit = GetTickCount();

						jason.hp -= 1;

						big_jason_got_hit_sound->Reset();
						big_jason_got_hit_sound->Play();
					}
				}
				for (int i = 0; i < enemy_cam_bullet.size(); i++)
				{
					enemy_cam_bullet[i].y += enemy_cam_bullet[i].movey;

					// enemy bullet hit jason
					if (jason.Bullet_collide(enemy_cam_bullet[i]) && GetTickCount() - char_start_get_hit >= 1000)
					{
						char_start_get_hit = GetTickCount();

						jason.hp -= 1;

						big_jason_got_hit_sound->Reset();
						big_jason_got_hit_sound->Play();
					}
				}

				// delete enemy bullet
				for (int i = 0; i < enemy_bug_bullet.size(); i++)
				{
					if (enemy_bug_bullet[i].x <= cam.x || enemy_bug_bullet[i].x >= cam.x + SCREEN_WIDTH ||
						enemy_bug_bullet[i].y <= cam.y || enemy_bug_bullet[i].y >= cam.y + SCREEN_HEIGHT)
					{
						enemy_bug_bullet.erase(enemy_bug_bullet.begin() + i);
						break;
					}
				}
				for (int i = 0; i < enemy_cam_bullet.size(); i++)
				{
					if (enemy_cam_bullet[i].y <= cam.y || enemy_cam_bullet[i].y >= cam.y + SCREEN_HEIGHT)
					{
						enemy_cam_bullet.erase(enemy_cam_bullet.begin() + i);
						break;
					}
				}

				// enemy bug shoot
				if (Dungeon_Enemy[i].id == 5 || Dungeon_Enemy[i].id == 9 || Dungeon_Enemy[i].id == 11 || Dungeon_Enemy[i].id == 12 ||
					Dungeon_Enemy[i].id == 17 || Dungeon_Enemy[i].id == 20)
				{
					float a = jason.x - Dungeon_Enemy[i].x;
					float b = jason.y - Dungeon_Enemy[i].y;

					if (abs(a) <= 224 && abs(b) <= 224 && GetTickCount() - enemy_start_shoot >= 5000)
					{
						enemy_start_shoot = GetTickCount();
						BULLET bu_temp;

						bu_temp.movex = Dungeon_Enemy[i].movex / 7;
						bu_temp.movey = Dungeon_Enemy[i].movey / 7;
						bu_temp.x = Dungeon_Enemy[i].x;
						bu_temp.y = Dungeon_Enemy[i].y;
						bu_temp.width = 16;
						bu_temp.height = 16;

						enemy_bug_bullet.push_back(bu_temp);

						enemy_bug_shoot_sound->Reset();
						enemy_bug_shoot_sound->Play();
					}
				}

				// enemy cam shoot
				if (Dungeon_Enemy[i].id == 21 || Dungeon_Enemy[i].id == 22)
				{
					if (jason.x<Dungeon_Enemy[i].x + Dungeon_Enemy[i].width && jason.x + jason.width>Dungeon_Enemy[i].x &&
						GetTickCount() - enemy_start_shoot >= 5000)
					{
						enemy_start_shoot = GetTickCount();

						BULLET bu_temp;
						bu_temp.x = Dungeon_Enemy[i].x;
						bu_temp.y = Dungeon_Enemy[i].y;
						bu_temp.movex = 0;
						bu_temp.movey = 6;
						bu_temp.width = 16;
						bu_temp.height = 52;

						enemy_cam_bullet.push_back(bu_temp);

						enemy_cam_shoot_sound->Reset();
						enemy_cam_shoot_sound->Play();
					}
				}

			}

			// enemy explode
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
		else if (mapid == 1 || mapid == 2 || mapid == 4)
		{
#pragma region Update Sophia and Cam
			// Sophia alive
			if (sophia.hp > 0 && player == 1)
			{
				// Sophia Jump
				if (map_info.sophia_collide_down(sophia))
				{
					sophia.movey = 0;
					if (KEY_DOWN(VK_SPACE))
					{
						sophia.movey = -SOPHIA_JUMP_SPEED;

						sophia_jump_sound->Reset();
						sophia_jump_sound->Play();
					}
				}
				// Sophia Bounce top
				else if (map_info.sophia_collide_up(sophia))
				{
					sophia.movey = 6;
				}
				// Sophia falling
				else
				{
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
					if (cam.y < map_info.height - SCREEN_HEIGHT - 16 && (sophia.y - cam.y) > SCREEN_HEIGHT / 2)
						cam.y += sophia.movey;
				}
				else if (sophia.movey < 0)
				{
					if (cam.y >= 16 && (sophia.y - cam.y) < SCREEN_HEIGHT / 2)
						cam.y += sophia.movey;
				}

				// Update bullet position
				for (int i = 0; i < sophia_bullet.size(); i++)
				{
					sophia_bullet[i].x += sophia_bullet[i].movex;
					sophia_bullet[i].y += sophia_bullet[i].movey;
				}

				// small jason go out
				if (KEY_DOWN(VK_RSHIFT))
				{
					// small jason
					player = 0;

					small_jason.x = sophia.x + 16;
					small_jason.y = sophia.y;
					small_jason.width = 16;
					small_jason.height = 32;
					small_jason.curframe = 0;
					small_jason.lastframe = 3;
					small_jason.animdelay = 2;
					small_jason.animcount = 0;
					small_jason.movex = 0;
					small_jason.movey = 0;
					small_jason.direction = 6;

					swap_player_sound->Reset();
					swap_player_sound->Play();
				}

				// "C" key pressed, then shoot
				if (KEY_DOWN(0x43))
				{
					if (sophia_bullet.size() < 3)
						if (GetTickCount() - char_start_shoot >= 100)
						{
							// Sound						
							sophia_shoot_sound->Reset();
							sophia_shoot_sound->Play();
							//

							char_start_shoot = GetTickCount();
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
						else if (map_info.sophia_bullet_collide_left(sophia_bullet[i]) || map_info.sophia_bullet_collide_right(sophia_bullet[i]))
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

							sophia_bullet_explosion_sound->Reset();
							sophia_bullet_explosion_sound->Play();
						}
					}
					else if (sophia_bullet[i].movey != 0)
					{
						if (sophia_bullet[i].y < cam.y)
						{
							sophia_bullet.erase(sophia_bullet.begin() + i);
						}
						else if (map_info.sophia_bullet_collide_up(sophia_bullet[i]))
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

							sophia_bullet_explosion_sound->Reset();
							sophia_bullet_explosion_sound->Play();
						}
					}
				}

				if (KEY_DOWN(VK_UP) && KEY_DOWN(VK_LEFT))
				{
					sophia.move_left_up();

					if (!map_info.sophia_collide_left(sophia) && sophia.x > 0)
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

					if (!map_info.sophia_collide_right(sophia) && sophia.x < map_info.width && sophia.x < map_info.width - 64)
					{
						sophia.x += sophia.movex;
						sophia.Update_body();
						sophia.Update_wheel();

						if (sophia.x - cam.x - 32 > SCREEN_HEIGHT / 2 && cam.x < map_info.width - 32 - SCREEN_WIDTH)
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

					if (!map_info.sophia_collide_left(sophia) && sophia.x > 0)
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

					if (!map_info.sophia_collide_right(sophia) && sophia.x < map_info.width - 64)
					{
						sophia.x += sophia.movex;
						sophia.Update_body();
						sophia.Update_wheel();

						if (sophia.x - cam.x - 32 > SCREEN_HEIGHT / 2 && cam.x < map_info.width - 32 - SCREEN_WIDTH)
							cam.x += sophia.movex;
					}
				}
				else
				{
					sophia.movex = 0;
				}

				// update sophia frame
				if (++sophia.animcount > sophia.animdelay)
				{
					sophia.animcount = 0;
					if (sophia.movex > 0)
						sophia.wheelcurframe++;
					else if (sophia.movex < 0)
						sophia.wheelcurframe--;

					if (sophia.wheelcurframe > sophia.wheellastframe)
						sophia.wheelcurframe = 0;
					else if (sophia.wheelcurframe < 0)
						sophia.wheelcurframe = 3;
				}
				// update explosion frame
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

						get_item_sound->Reset();
						get_item_sound->Play();
					}
				}
				for (int i = 0; i < items_area3_scene2.size(); i++)
				{
					if (items_area3_scene2[i].Sophia_collide(sophia))
					{
						items_area3_scene2.erase(items_area3_scene2.begin() + i);
						if (sophia.hp < 8)
							sophia.hp += 1;

						get_item_sound->Reset();
						get_item_sound->Play();
					}
				}

			}
			// small jason
			else if (sophia.hp > 0 && player == 0)
			{
				if (map_info.sophia_collide_down(small_jason))
				{
					small_jason.movey = 0;
					if (KEY_DOWN(VK_SPACE))
					{
						small_jason.movey = -16;

						small_jason_jump_sound->Reset();
						small_jason_jump_sound->Play();
					}
				}
				else if (map_info.sophia_collide_up(small_jason))
				{
					small_jason.movey = 6;
				}
				// falling
				else
				{
					small_jason.movey += 1;
					if (small_jason.movey >= 8)
						small_jason.movey = 8;
				}
				small_jason.y += small_jason.movey;

				if (small_jason.movey > 0)
				{
					if (cam.y < map_info.height - SCREEN_HEIGHT - 16 && (small_jason.y - cam.y) > SCREEN_HEIGHT / 2)
						cam.y += small_jason.movey;
				}
				else if (small_jason.movey < 0)
				{
					if (cam.y >= 16 && (small_jason.y - cam.y) < SCREEN_HEIGHT / 2)
						cam.y += small_jason.movey;
				}

				if (small_jason.small_jason_collide_sophia(sophia))
				{
					if (KEY_DOWN(VK_LSHIFT))
					{
						player = 1;

						swap_player_sound->Reset();
						swap_player_sound->Play();
					}
				}


				if (KEY_DOWN(VK_LEFT))
				{
					small_jason.move_left();

					if (!map_info.sophia_collide_left(small_jason) && small_jason.x > 0)
					{
						small_jason.x += small_jason.movex;

						if (small_jason.x - cam.x - 32 < SCREEN_HEIGHT / 2 && cam.x > 32)
							cam.x += small_jason.movex;
					}
				}
				else if (KEY_DOWN(VK_RIGHT))
				{
					small_jason.move_right();

					if (!map_info.sophia_collide_right(small_jason) && small_jason.x < map_info.width - 64)
					{
						small_jason.x += small_jason.movex;

						if (small_jason.x - cam.x - 32 > SCREEN_HEIGHT / 2 && cam.x < map_info.width - 32 - SCREEN_WIDTH)
							cam.x += small_jason.movex;
					}
				}
				else
				{
					small_jason.movex = 0;
				}

				if (++small_jason.animcount > small_jason.animdelay)
				{
					small_jason.animcount = 0;
					if (small_jason.movex != 0)
						small_jason.curframe++;
					else
						small_jason.curframe = 0;

					if (small_jason.curframe > small_jason.lastframe)
						small_jason.curframe = 0;
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

					sophia.x = 0;
					sophia.y = 0;

					sophia_die_sound->Play();
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
#pragma region Update Enemy Area3 Scene1, Tele1

			// Tele
			if (map_info.sophia_collide_tele1(sophia))
			{
				map_info = map_area3_scene2;
				mapid = 2;

				cam.x = 2016;
				cam.y = 32;
				sophia.x = 2464;
				sophia.y = 280;
			}

			for (int i = 0; i < Area3_Scene1_Enemy.size(); i++)
			{
				// sophia get hit by enemy
				if (Area3_Scene1_Enemy[i].Sophia_collide(sophia) && GetTickCount() - char_start_get_hit >= 1000)
				{
					char_start_get_hit = GetTickCount();
					sophia.hp -= 1;

					sophia_got_hit_sound->Stop();
					sophia_got_hit_sound->Reset();
					sophia_got_hit_sound->Play();
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

						enemy_got_hit_sound->Reset();
						enemy_got_hit_sound->Play();

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

							enemy_die_sound->Reset();
							enemy_die_sound->Play();
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

			// Tele 2
			if (map_info.sophia_collide_tele2(sophia))
			{
				map_info = map_area3_scene3;
				mapid = 4;

				cam.x = 0;
				cam.y = 16;

				sophia.x = 32;
				sophia.y = 280;
			}

			for (int i = 0; i < Area3_Scene2_Enemy.size(); i++)
			{
				// sophia get hit
				if (Area3_Scene2_Enemy[i].Sophia_collide(sophia) && GetTickCount() - char_start_get_hit >= 1000)
				{
					char_start_get_hit = GetTickCount();
					sophia.hp -= 1;

					sophia_got_hit_sound->Stop();
					sophia_got_hit_sound->Reset();
					sophia_got_hit_sound->Play();
				}

				// sophia bullet hit enemy
				for (int j = 0; j < sophia_bullet.size(); j++)
				{
					if (Area3_Scene2_Enemy[i].Bullet_collide(sophia_bullet[j]) && GetTickCount() - enemy_start_get_hit >= 30)
					{
						enemy_start_get_hit = GetTickCount();
						Area3_Scene2_Enemy[i].hp--;

						enemy_got_hit_sound->Reset();
						enemy_got_hit_sound->Play();

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

							enemy_die_sound->Reset();
							enemy_die_sound->Play();
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
				case 1:
					if (sophia.x <= 2112 && Area3_Scene2_Enemy[i].y >= 64)
					{
						Area3_Scene2_Enemy[i].isActivate = true;
						Area3_Scene2_Enemy[i].image[0] = enemy_ball_right_gray_image[0];
						Area3_Scene2_Enemy[i].image[1] = enemy_ball_right_gray_image[1];
						Area3_Scene2_Enemy[i].image[2] = enemy_ball_right_gray_image[2];
					}
					else if (Area3_Scene2_Enemy[i].y < 64)
						Area3_Scene2_Enemy[i].isActivate = false;

					if (Area3_Scene2_Enemy[i].isActivate)
					{
						Area3_Scene2_Enemy[i].x += 2;
						Area3_Scene2_Enemy[i].y = (-5.0 / 128) * ((float)Area3_Scene2_Enemy[i].x * (float)Area3_Scene2_Enemy[i].x) +
							165 * (float)Area3_Scene2_Enemy[i].x - 174016;
					}
					break;
				case 2:
					if (Area3_Scene2_Enemy[i].x <= 1632)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 1792)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 3:
					if (sophia.x < 1824 && Area3_Scene2_Enemy[i].isDraw == false)
					{
						Area3_Scene2_Enemy[i].isDraw = true;
						teeth_arrive_sound->Reset();
						teeth_arrive_sound->Play();
					}
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
				case 5:
					if (sophia.x <= 1376)
					{
						Area3_Scene2_Enemy[i].isActivate = true;
						Area3_Scene2_Enemy[i].image[0] = enemy_ball_right_gray_image[0];
						Area3_Scene2_Enemy[i].image[1] = enemy_ball_right_gray_image[1];
						Area3_Scene2_Enemy[i].image[2] = enemy_ball_right_gray_image[2];
					}
					else if (Area3_Scene2_Enemy[i].y < 64)
						Area3_Scene2_Enemy[i].isActivate = false;

					if (Area3_Scene2_Enemy[i].isActivate)
					{
						Area3_Scene2_Enemy[i].x += 2;
						Area3_Scene2_Enemy[i].y = (-5.0 / 128) * ((float)Area3_Scene2_Enemy[i].x * (float)Area3_Scene2_Enemy[i].x) +
							(215.0 / 2) * (float)Area3_Scene2_Enemy[i].x - 73608;
					}
					break;
				case 6:
					if (Area3_Scene2_Enemy[i].x <= 960)
						Area3_Scene2_Enemy[i].movex = 4;
					if (Area3_Scene2_Enemy[i].x >= 1088)
						Area3_Scene2_Enemy[i].movex = -4;
					Area3_Scene2_Enemy[i].x += Area3_Scene2_Enemy[i].movex;
					break;
				case 7:
					if (sophia.x < 1088 && Area3_Scene2_Enemy[i].isDraw == false)
					{
						Area3_Scene2_Enemy[i].isDraw = true;
						teeth_arrive_sound->Reset();
						teeth_arrive_sound->Play();
					}
					if (Area3_Scene2_Enemy[i].isDraw == true)
					{
						Area3_Scene2_Enemy[i].x += 5;
						Area3_Scene2_Enemy[i].y = 560 + 48 * cos(float(Area3_Scene2_Enemy[i].x) / 32);
						if (Area3_Scene2_Enemy[i].x > cam.x + SCREEN_WIDTH)
							Area3_Scene2_Enemy.erase(Area3_Scene2_Enemy.begin() + i);
					}
					break;
				case 8:
					if (sophia.x < 832 && Area3_Scene2_Enemy[i].isDraw == false) {
						Area3_Scene2_Enemy[i].isDraw = true;
						teeth_arrive_sound->Reset();
						teeth_arrive_sound->Play();
					}
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
				case 14:
					if (sophia.y >= 704 && sophia.x >= 1344 && Area3_Scene2_Enemy[i].y >= 64)
					{
						Area3_Scene2_Enemy[i].isActivate = true;
						Area3_Scene2_Enemy[i].image[0] = enemy_ball_right_gray_image[0];
						Area3_Scene2_Enemy[i].image[1] = enemy_ball_right_gray_image[1];
						Area3_Scene2_Enemy[i].image[2] = enemy_ball_right_gray_image[2];
					}
					else if (Area3_Scene2_Enemy[i].y < 544)
						Area3_Scene2_Enemy[i].isActivate = false;

					if (Area3_Scene2_Enemy[i].isActivate)
					{
						Area3_Scene2_Enemy[i].x += 2;
						Area3_Scene2_Enemy[i].y = (-5.0 / 128) * ((float)Area3_Scene2_Enemy[i].x * (float)Area3_Scene2_Enemy[i].x) +
							(215.0 / 2) * (float)Area3_Scene2_Enemy[i].x - 73096;
					}
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
					if (sophia.x > 1920 && sophia.y > 832 && Area3_Scene2_Enemy[i].isDraw == false) {
						Area3_Scene2_Enemy[i].isDraw = true;
						teeth_arrive_sound->Reset();
						teeth_arrive_sound->Play();
					}
					if (Area3_Scene2_Enemy[i].isDraw == true)
					{
						Area3_Scene2_Enemy[i].x += 5;
						Area3_Scene2_Enemy[i].y = 816 + 48 * cos(float(Area3_Scene2_Enemy[i].x) / 32);
						if (Area3_Scene2_Enemy[i].x > cam.x + SCREEN_WIDTH)
							Area3_Scene2_Enemy.erase(Area3_Scene2_Enemy.begin() + i);
					}
					break;
				case 19:
					if (sophia.x > 1920 && sophia.y > 832 && Area3_Scene2_Enemy[i].isDraw == false) {
						Area3_Scene2_Enemy[i].isDraw = true;
						teeth_arrive_sound->Reset();
						teeth_arrive_sound->Play();
					}
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
		else if (mapid == 4)
		{
#pragma region Tele3
			// small jason collide tele3
			if (map_info.sophia_collide_tele3(small_jason))
			{
				if (KEY_DOWN(VK_UP))
				{
					player = 2;
					jason.hp = sophia.hp;

					mapid = 3;
					map_info = map_dungeon;

					cam.x = 0;
					cam.y = 16;

					switch_scene_sound->Play();
				}
			}

#pragma endregion
		}
	}

#pragma region Draw

	if (d3ddev->BeginScene())
	{
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
			}
			// Draw jason die
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

			// Draw items in dungeon
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

			for (int i = 0; i < enemy_bug_bullet.size(); i++)
			{
				D3DXVECTOR3 positioneshoot((float)enemy_bug_bullet[i].x - cam.x, (float)enemy_bug_bullet[i].y - cam.y, 0);
				sprite_handler->Draw(
					enemy_bug_bullet_image[0],
					NULL, NULL,
					&positioneshoot,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			for (int i = 0; i < enemy_cam_bullet.size(); i++)
			{
				D3DXVECTOR3 positioneshoot((float)enemy_cam_bullet[i].x - cam.x, (float)enemy_cam_bullet[i].y - cam.y, 0);
				sprite_handler->Draw(
					enemy_cam_bullet_image[0],
					NULL, NULL,
					&positioneshoot,
					D3DCOLOR_XRGB(255, 255, 255));
			}

#pragma endregion
		}
		else if (mapid == 1 || mapid == 2 || mapid == 4)
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

				// Draw sophia bullet
				for (int i = 0; i < sophia_bullet.size(); i++)
				{
					D3DXVECTOR3 positionbullet((float)sophia_bullet[i].x - cam.x, (float)sophia_bullet[i].y - cam.y, 0);
					sprite_handler->Draw(
						sophia_bullet_image[sophia_bullet[i].direction],
						NULL, NULL,
						&positionbullet,
						D3DCOLOR_XRGB(255, 255, 255));
				}

				// Draw explosion
				for (int i = 0; i < explosion.size(); i++)
				{
					D3DXVECTOR3 positionexplosion((float)explosion[i].x - cam.x, (float)explosion[i].y - cam.y, 0);
					sprite_handler->Draw(
						area3_bullet_explosion_image[explosion[i].curframe],
						NULL, NULL,
						&positionexplosion,
						D3DCOLOR_XRGB(255, 255, 255));
				}


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

			// Draw small jason
			if (player == 0)
			{
				D3DXVECTOR3 positionsmj((float)small_jason.x - cam.x, (float)small_jason.y - cam.y, 0);

				if (small_jason.direction == 6)
				{
					sprite_handler->Draw(
						small_jason_image_right[small_jason.curframe],
						NULL, NULL,
						&positionsmj,
						D3DCOLOR_XRGB(255, 255, 255));
				}
				else if (small_jason.direction == 4)
				{
					sprite_handler->Draw(
						small_jason_image_left[small_jason.curframe],
						NULL, NULL,
						&positionsmj,
						D3DCOLOR_XRGB(255, 255, 255));
				}

			}
#pragma endregion
		}

		if (mapid == 1)
		{
#pragma region Draw Enemy Area3 Scene1

			// Draw items
			for (int i = 0; i < items_area3_scene1.size(); i++)
			{
				D3DXVECTOR3 positionitem((float)items_area3_scene1[i].x - cam.x, (float)items_area3_scene1[i].y - cam.y, 0);
				sprite_handler->Draw(
					P_item_image[0],
					NULL, NULL,
					&positionitem,
					D3DCOLOR_XRGB(255, 255, 255));
			}

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
			// Draw items
			for (int i = 0; i < items_area3_scene2.size(); i++)
			{
				D3DXVECTOR3 positionitem((float)items_area3_scene2[i].x - cam.x, (float)items_area3_scene2[i].y - cam.y, 0);
				sprite_handler->Draw(
					P_item_image[0],
					NULL, NULL,
					&positionitem,
					D3DCOLOR_XRGB(255, 255, 255));
			}

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

			d3ddev->StretchRect(map_info.image[map_info.matrix[cam.y / TILE_SIZE][j] - 1],
				&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);
		}
		// Draw last cell of line
		rect_des.left = rect_des.right;
		rect_des.right = rect_des.left + offset_x;

		rect_src.left = 0;
		rect_src.right = offset_x;

		d3ddev->StretchRect(map_info.image[map_info.matrix[cam.y / TILE_SIZE][j] - 1],
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

				d3ddev->StretchRect(map_info.image[map_info.matrix[i][j] - 1],
					&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);
			}

			rect_des.left = rect_des.right;
			rect_des.right = rect_des.left + offset_x;

			rect_src.left = 0;
			rect_src.right = offset_x;

			d3ddev->StretchRect(map_info.image[map_info.matrix[i][j] - 1],
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

			d3ddev->StretchRect(map_info.image[map_info.matrix[(SCREEN_HEIGHT + cam.y) / TILE_SIZE][j] - 1],
				&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);
		}

		rect_des.left = rect_des.right;
		rect_des.right = rect_des.left + offset_x;

		rect_src.left = 0;
		rect_src.right = offset_x;

		d3ddev->StretchRect(map_info.image[map_info.matrix[(SCREEN_HEIGHT + cam.y) / TILE_SIZE][j] - 1],
			&rect_src, backbuffer, &rect_des, D3DTEXF_NONE);
#pragma endregion

#pragma region Draw Map cover player

		if (mapid == 1)
		{
			D3DXVECTOR3 positiontile1((float)32 * 2 - cam.x, (float)32 * 23 - cam.y, 0);
			sprite_handler->Draw(
				gate20,
				NULL, NULL,
				&positiontile1,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile2((float)32 * 2 - cam.x, (float)32 * 24 - cam.y, 0);
			sprite_handler->Draw(
				gate28,
				NULL, NULL,
				&positiontile2,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile3((float)32 * 1 - cam.x, (float)32 * 23 - cam.y, 0);
			sprite_handler->Draw(
				gate19,
				NULL, NULL,
				&positiontile3,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile4((float)32 * 1 - cam.x, (float)32 * 24 - cam.y, 0);
			sprite_handler->Draw(
				gate27,
				NULL, NULL,
				&positiontile4,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile5((float)32 * 2 - cam.x, (float)32 * 7 - cam.y, 0);
			sprite_handler->Draw(
				gate20,
				NULL, NULL,
				&positiontile5,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile6((float)32 * 2 - cam.x, (float)32 * 8 - cam.y, 0);
			sprite_handler->Draw(
				gate28,
				NULL, NULL,
				&positiontile6,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile7((float)32 * 1 - cam.x, (float)32 * 7 - cam.y, 0);
			sprite_handler->Draw(
				gate19,
				NULL, NULL,
				&positiontile7,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile8((float)32 * 1 - cam.x, (float)32 * 8 - cam.y, 0);
			sprite_handler->Draw(
				gate27,
				NULL, NULL,
				&positiontile8,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile9((float)32 * 0 - cam.x, (float)32 * 7 - cam.y, 0);
			sprite_handler->Draw(
				gate19,
				NULL, NULL,
				&positiontile9,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile10((float)32 * 0 - cam.x, (float)32 * 8 - cam.y, 0);
			sprite_handler->Draw(
				gate27,
				NULL, NULL,
				&positiontile10,
				D3DCOLOR_XRGB(255, 255, 255));
		}
		else if (mapid == 2)
		{
			D3DXVECTOR3 positiontile1((float)32 * 77 - cam.x, (float)32 * 8 - cam.y, 0);
			sprite_handler->Draw(
				gate18,
				NULL, NULL,
				&positiontile1,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile2((float)32 * 77 - cam.x, (float)32 * 9 - cam.y, 0);
			sprite_handler->Draw(
				gate26,
				NULL, NULL,
				&positiontile2,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile3((float)32 * 78 - cam.x, (float)32 * 8 - cam.y, 0);
			sprite_handler->Draw(
				gate19,
				NULL, NULL,
				&positiontile3,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile4((float)32 * 78 - cam.x, (float)32 * 9 - cam.y, 0);
			sprite_handler->Draw(
				gate27,
				NULL, NULL,
				&positiontile4,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile5((float)32 * 77 - cam.x, (float)32 * 24 - cam.y, 0);
			sprite_handler->Draw(
				gate18,
				NULL, NULL,
				&positiontile5,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile6((float)32 * 77 - cam.x, (float)32 * 25 - cam.y, 0);
			sprite_handler->Draw(
				gate26,
				NULL, NULL,
				&positiontile6,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile7((float)32 * 78 - cam.x, (float)32 * 24 - cam.y, 0);
			sprite_handler->Draw(
				gate19,
				NULL, NULL,
				&positiontile7,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile8((float)32 * 78 - cam.x, (float)32 * 25 - cam.y, 0);
			sprite_handler->Draw(
				gate27,
				NULL, NULL,
				&positiontile8,
				D3DCOLOR_XRGB(255, 255, 255));
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

			D3DXVECTOR3 positiontile27((float)32 * 23 - cam.x, (float)32 * 77 - cam.y, 0);
			sprite_handler->Draw(
				tilemap11,
				NULL, NULL,
				&positiontile27,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile28((float)32 * 24 - cam.x, (float)32 * 77 - cam.y, 0);
			sprite_handler->Draw(
				tilemap12,
				NULL, NULL,
				&positiontile28,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile29((float)32 * 23 - cam.x, (float)32 * 78 - cam.y, 0);
			sprite_handler->Draw(
				tilemap23,
				NULL, NULL,
				&positiontile29,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile30((float)32 * 24 - cam.x, (float)32 * 78 - cam.y, 0);
			sprite_handler->Draw(
				tilemap24,
				NULL, NULL,
				&positiontile30,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile31((float)32 * 23 - cam.x, (float)32 * 79 - cam.y, 0);
			sprite_handler->Draw(
				tilemap35,
				NULL, NULL,
				&positiontile31,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile32((float)32 * 24 - cam.x, (float)32 * 79 - cam.y, 0);
			sprite_handler->Draw(
				tilemap36,
				NULL, NULL,
				&positiontile32,
				D3DCOLOR_XRGB(255, 255, 255));

			for (int i = 18; i < 22; i++)
			{
				D3DXVECTOR3 positiontile5((float)32 * i - cam.x, (float)32 * 77 - cam.y, 0);
				sprite_handler->Draw(
					tilemap9,
					NULL, NULL,
					&positiontile5,
					D3DCOLOR_XRGB(255, 255, 255));

				D3DXVECTOR3 positiontile6((float)32 * i - cam.x, (float)32 * 78 - cam.y, 0);
				sprite_handler->Draw(
					tilemap21,
					NULL, NULL,
					&positiontile6,
					D3DCOLOR_XRGB(255, 255, 255));
			}

			for (int i = 26; i < 30; i++)
			{
				D3DXVECTOR3 positiontile5((float)32 * i - cam.x, (float)32 * 77 - cam.y, 0);
				sprite_handler->Draw(
					tilemap9,
					NULL, NULL,
					&positiontile5,
					D3DCOLOR_XRGB(255, 255, 255));

				D3DXVECTOR3 positiontile6((float)32 * i - cam.x, (float)32 * 78 - cam.y, 0);
				sprite_handler->Draw(
					tilemap21,
					NULL, NULL,
					&positiontile6,
					D3DCOLOR_XRGB(255, 255, 255));
			}
			D3DXVECTOR3 positiontile33((float)32 * 22 - cam.x, (float)32 * 77 - cam.y, 0);
			sprite_handler->Draw(
				tilemap10,
				NULL, NULL,
				&positiontile33,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile34((float)32 * 22 - cam.x, (float)32 * 78 - cam.y, 0);
			sprite_handler->Draw(
				tilemap22,
				NULL, NULL,
				&positiontile34,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 positiontile35((float)32 * 25 - cam.x, (float)32 * 77 - cam.y, 0);
			sprite_handler->Draw(
				tilemap8,
				NULL, NULL,
				&positiontile35,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile36((float)32 * 25 - cam.x, (float)32 * 78 - cam.y, 0);
			sprite_handler->Draw(
				tilemap20,
				NULL, NULL,
				&positiontile36,
				D3DCOLOR_XRGB(255, 255, 255));

		}
		else if (mapid == 4)
		{
			D3DXVECTOR3 positiontile5((float)32 * 2 - cam.x, (float)32 * 8 - cam.y, 0);
			sprite_handler->Draw(
				gate20,
				NULL, NULL,
				&positiontile5,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile6((float)32 * 2 - cam.x, (float)32 * 9 - cam.y, 0);
			sprite_handler->Draw(
				gate28,
				NULL, NULL,
				&positiontile6,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile7((float)32 * 1 - cam.x, (float)32 * 8 - cam.y, 0);
			sprite_handler->Draw(
				gate19,
				NULL, NULL,
				&positiontile7,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile8((float)32 * 1 - cam.x, (float)32 * 9 - cam.y, 0);
			sprite_handler->Draw(
				gate27,
				NULL, NULL,
				&positiontile8,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile9((float)32 * 0 - cam.x, (float)32 * 8 - cam.y, 0);
			sprite_handler->Draw(
				gate19,
				NULL, NULL,
				&positiontile9,
				D3DCOLOR_XRGB(255, 255, 255));
			D3DXVECTOR3 positiontile10((float)32 * 0 - cam.x, (float)32 * 9 - cam.y, 0);
			sprite_handler->Draw(
				gate27,
				NULL, NULL,
				&positiontile10,
				D3DCOLOR_XRGB(255, 255, 255));
		}

#pragma endregion

#pragma region Draw HP Bar

		if (player == 1 || player == 0)
		{
			if (sophia.hp >= 0)
			{
				D3DXVECTOR3 positionhpbar(16, 256, 0);
				sprite_handler->Draw(
					hp_bar_image[sophia.hp],
					NULL, NULL,
					&positionhpbar,
					D3DCOLOR_XRGB(255, 255, 255));
			}
		}
		else if (player == 2)
		{
			if (jason.hp >= 0)
			{
				D3DXVECTOR3 positionhpbar(16, 256, 0);
				sprite_handler->Draw(
					hp_bar_image[jason.hp],
					NULL, NULL,
					&positionhpbar,
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
