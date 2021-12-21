#include "sophia.h"

void SOPHIA::Update_wheel()
{
	wheelleft_x = x, wheelleft_y = y + 16;
	wheelright_x = x + 32, wheelright_y = y + 16;
	if (direction == 48 || direction == 68)
	{
		midwheel_x = x + 16, midwheel_y = y + 8;
	}
	else
		midwheel_x = x + 16, midwheel_y = y + 16;
}

void SOPHIA::Update_body()
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
	else if (direction == 48)
	{
		body_x = x + 16, body_y = y - 16;
		gun_x = x + 16, gun_y = y - 32;
	}
	else if (direction == 68)
	{
		body_x = x, body_y = y - 16;
		gun_x = x + 16, gun_y = y - 32;
	}
}

void SOPHIA::move_left()
{
	direction = 4;
	movex = -4;
}
void SOPHIA::move_right()
{
	direction = 6;
	movex = 4;
}

void SOPHIA::move_left_up()
{
	direction = 48;
	movex = -4;
}

void SOPHIA::move_right_up()
{
	direction = 68;
	movex = 4;
}

bool SOPHIA::small_jason_collide_sophia(SOPHIA sophia)
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