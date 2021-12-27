#ifndef _MAP_H
#define _MAP_H

#include "map.h"
#include "sophia.h"
#include "sprite.h"
#include "game.h"

class SPRITE;
class SOPHIA;
class BULLET;

class MAP {
public:
	int height;
	int width;
	int matrix[128][80];
	LPDIRECT3DSURFACE9 image[112];

	// Dungeon
	bool isSolid_Dungeon(int noColumn, int noRow);
	bool isTrap_Dungeon(int noColumn, int noRow);
	bool isBreakable_Wall(int noColumn, int noRow);

	bool jason_collide_right(SPRITE s);
	bool jason_collide_left(SPRITE s);
	bool jason_collide_up(SPRITE s);
	bool jason_collide_down(SPRITE s);

	bool jason_collide_trap_right(SPRITE s);
	bool jason_collide_trap_left(SPRITE s);
	bool jason_collide_trap_up(SPRITE s);
	bool jason_collide_trap_down(SPRITE s);

	bool jason_bullet_collide_right(BULLET bullet);
	bool jason_bullet_collide_left(BULLET bullet);
	bool jason_bullet_collide_up(BULLET bullet);
	bool jason_bullet_collide_down(BULLET bullet);

	// Area3
	bool isSolid_Area3(int noColumn, int noRow);

	bool sophia_collide_right(SOPHIA sophia);
	bool sophia_collide_left(SOPHIA sophia);
	bool sophia_collide_up(SOPHIA sophia);
	bool sophia_collide_down(SOPHIA sophia);

	bool sophia_bullet_collide_right(BULLET bullet);
	bool sophia_bullet_collide_left(BULLET bullet);
	bool sophia_bullet_collide_up(BULLET bullet);

	bool sophia_collide_tele1(SOPHIA sophia);
	bool sophia_collide_tele2(SOPHIA sophia);
	bool sophia_collide_tele3(SOPHIA sophia);

	bool enemy_collide_down(SPRITE s);
	bool enemy_collide_left(SPRITE s);
	bool enemy_collide_right(SPRITE s);
};

#endif