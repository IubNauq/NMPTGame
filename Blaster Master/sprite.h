#ifndef _SPRITE_H
#define _SPRITE_H

#include "sprite.h"
#include "sophia.h"
#include "game.h"

class SOPHIA;
class BULLET;

class SPRITE {
public:
	int x, y;
	int width, height;
	float movex, movey;
	int curframe, lastframe;
	int animdelay, animcount;
	int direction;	// 2: down, 4: left, 6: right, 8: up 
	int id;
	bool isDraw;
	int hp = 1;

	bool isFire;

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
