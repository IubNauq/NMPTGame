#include "sprite.h"



void SPRITE::move_right()
{
	direction = 6;
	movex = JASON_MOVE_SPEED;
	movey = 0;
}

void SPRITE::move_left()
{
	direction = 4;
	movex = -JASON_MOVE_SPEED;
	movey = 0;
}

void SPRITE::move_up()
{
	direction = 8;
	movex = 0;
	movey = -JASON_MOVE_SPEED;
}

void SPRITE::move_down()
{
	direction = 2;
	movex = 0;
	movey = JASON_MOVE_SPEED;
}

bool SPRITE::Sophia_collide(SOPHIA sophia)
{
	int sophiatop = sophia.y;
	int sophiabottom = sophia.y + sophia.height;
	int sophialeft = sophia.x;
	int sophiaright = sophia.x + sophia.width;

	int spritetop = y;
	int spritebottom = y + height;
	int spriteleft = x;
	int spriteright = x + width;

	if (sophiatop < spritebottom && sophiabottom > spritetop && sophiaright > spriteleft && sophialeft < spriteright)
		return true;
	return false;
}

bool SPRITE::Bullet_collide(BULLET bullet)
{
	int bullettop = bullet.y;
	int bulletbottom = bullet.y + bullet.height;
	int bulletleft = bullet.x;
	int bulletright = bullet.x + bullet.width;

	int spritetop = y;
	int spritebottom = y + height;
	int spriteleft = x;
	int spriteright = x + width;

	if (bullettop < spritebottom && bulletbottom > spritetop && bulletright > spriteleft && bulletleft < spriteright)
		return true;
	return false;
}

bool SPRITE::Jason_collide(SPRITE jason)
{
	int jasontop = jason.y;
	int jasonbottom = jason.y + jason.height;
	int jasonleft = jason.x;
	int jasonright = jason.x + jason.width;

	int spritetop = y;
	int spritebottom = y + height;
	int spriteleft = x;
	int spriteright = x + width;

	if (jasontop < spritebottom && jasonbottom > spritetop && jasonright > spriteleft && jasonleft < spriteright)
		return true;
	return false;
}