#ifndef _SPRITE_H
#define _SPRITE_H

#include "sprite.h"
#include "sophia.h"
#include "game.h"

#define JASON_MOVE_SPEED 4;

class SOPHIA;
class BULLET;

class SPRITE {
public:
	float x, y;
	int width, height;
	float movex, movey;
	int curframe, lastframe;
	int animdelay, animcount;
	int direction;	// 2: down, 4: left, 6: right, 8: up 
	int id;
	bool isDraw;
	bool isActivate = false;
	int hp = 1;

	bool isFire; // drop enemy

	// Boss
	int BossCurPos = 0;
	bool isBossMoving = false;
	bool canHit = false;
	int numOfbullet = 0;
	bool isDamaged = false;

	LPDIRECT3DTEXTURE9 image[5];

	void move_right();
	void move_left();
	void move_up();
	void move_down();

	// Sophia collide with Enemy
	bool Sophia_collide(SOPHIA sophia);
	
	// Jason collide with Enemy
	bool Jason_collide(SPRITE jason);

	// Monster collide with bullet
	bool Bullet_collide(BULLET bullet);
};

#endif
