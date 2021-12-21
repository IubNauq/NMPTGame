#include "map.h"

vector<int> solid_dungeon = { 5,8,9,10,16,17,18,19,20,21,22,32,33,34,45,70 };
vector<int> trap_dungeon = { 39 };
bool MAP::isSolid_Dungeon(int noColumn, int noRow)
{
	for (int i = 0; i < solid_dungeon.size(); i++)
	{
		if (matrix[noRow][noColumn] == solid_dungeon[i])
		{
			return true;
		}
	}
	return false;
}
bool MAP::isTrap_Dungeon(int noColumn, int noRow)
{
	for (int i = 0; i < trap_dungeon.size(); i++)
	{
		if (matrix[noRow][noColumn] == trap_dungeon[i])
		{
			return true;
		}
	}
	return false;
}

bool MAP::isBreakable_Wall(int noColumn, int noRow)
{
	if (matrix[noRow][noColumn] == 70)
	{
		matrix[noRow][noColumn] = 79;
		return true;
	}
	return false;
}

bool MAP::jason_collide_right(SPRITE s)
{
	for (int i = (s.y + s.height / 2) / TILE_SIZE; i <= (s.y + s.height) / TILE_SIZE; i++)
	{
		if (isSolid_Dungeon((s.x + s.width + 4) / TILE_SIZE, i))
		{
			return true;
		}
	}
	return false;
}
bool MAP::jason_collide_left(SPRITE s)
{
	for (int i = (s.y + s.height / 2) / TILE_SIZE; i <= (s.y + s.height) / TILE_SIZE; i++)
	{
		if (isSolid_Dungeon((s.x - 4) / TILE_SIZE, i))
		{
			return true;
		}
	}
	return false;
}
bool MAP::jason_collide_up(SPRITE s)
{
	for (int j = s.x / TILE_SIZE; j <= (s.x + s.width) / TILE_SIZE; j++)
	{
		if (isSolid_Dungeon(j, (s.y - 4 + s.height / 2) / TILE_SIZE))
		{
			return true;
		}
	}
	return false;
}
bool MAP::jason_collide_down(SPRITE s)
{
	for (int j = s.x / TILE_SIZE; j <= (s.x + s.width) / TILE_SIZE; j++)
	{
		if (isSolid_Dungeon(j, (s.y + 4 + s.height) / TILE_SIZE))
		{
			return true;
		}
	}
	return false;
}

bool MAP::jason_collide_trap_right(SPRITE s)
{
	for (int i = (s.y + s.height / 2) / TILE_SIZE; i <= (s.y + s.height) / TILE_SIZE; i++)
	{
		if (isTrap_Dungeon((s.x + s.width - 24) / TILE_SIZE, i))
		{
			return true;
		}
	}
	return false;
}
bool MAP::jason_collide_trap_left(SPRITE s)
{
	for (int i = (s.y + s.height / 2) / TILE_SIZE; i <= (s.y + s.height) / TILE_SIZE; i++)
	{
		if (isTrap_Dungeon((s.x + 24) / TILE_SIZE, i))
		{
			return true;
		}
	}
	return false;
}
bool MAP::jason_collide_trap_up(SPRITE s)
{
	for (int j = s.x / TILE_SIZE; j <= (s.x + s.width) / TILE_SIZE; j++)
	{
		if (isTrap_Dungeon(j, (s.y + 16 + s.height / 2) / TILE_SIZE))
		{
			return true;
		}
	}
	return false;
}
bool MAP::jason_collide_trap_down(SPRITE s)
{
	for (int j = s.x / TILE_SIZE; j <= (s.x + s.width) / TILE_SIZE; j++)
	{
		if (isTrap_Dungeon(j, (s.y + s.height - 16) / TILE_SIZE))
		{
			return true;
		}
	}
	return false;
}

bool MAP::jason_bullet_collide_right(BULLET bullet)
{
	for (int i = (bullet.y + bullet.height / 2) / TILE_SIZE; i <= (bullet.y + bullet.height) / TILE_SIZE; i++)
	{
		if (isBreakable_Wall((bullet.x + bullet.width) / TILE_SIZE, i))
		{
			return true;
		}
		if (isSolid_Dungeon((bullet.x + bullet.width) / TILE_SIZE, i))
		{
			return true;
		}
	}
	return false;
}
bool MAP::jason_bullet_collide_left(BULLET bullet)
{
	for (int i = (bullet.y + bullet.height / 2) / TILE_SIZE; i <= (bullet.y + bullet.height) / TILE_SIZE; i++)
	{
		if (isBreakable_Wall((bullet.x) / TILE_SIZE, i))
		{
			return true;
		}
		if (isSolid_Dungeon((bullet.x) / TILE_SIZE, i))
		{
			return true;
		}
	}
	return false;
}
bool MAP::jason_bullet_collide_up(BULLET bullet)
{
	for (int j = bullet.x / TILE_SIZE; j <= (bullet.x + bullet.width) / TILE_SIZE; j++)
	{
		if (isBreakable_Wall(j, bullet.y / TILE_SIZE))
		{
			return true;
		}
		if (isSolid_Dungeon(j, bullet.y / TILE_SIZE))
		{
			return true;
		}
	}
	return false;
}
bool MAP::jason_bullet_collide_down(BULLET bullet)
{
	for (int j = bullet.x / TILE_SIZE; j <= (bullet.x + bullet.width) / TILE_SIZE; j++)
	{
		if (isBreakable_Wall(j, (bullet.y + bullet.height) / TILE_SIZE))
		{
			return true;
		}
		if (isSolid_Dungeon(j, (bullet.y + bullet.height) / TILE_SIZE))
		{
			return true;
		}
	}
	return false;
}

vector<int> solid_area3 = { 6,15,76,77,84,85,86 };
bool MAP::isSolid_Area3(int noColumn, int noRow)
{
	for (int i = 0; i < solid_area3.size(); i++)
	{
		if (matrix[noRow][noColumn] == solid_area3[i])
		{
			return true;
		}
	}
	return false;
}

bool MAP::sophia_collide_right(SOPHIA sophia)
{
	for (int i = (sophia.y + sophia.height / 2) / TILE_SIZE; i <= (sophia.y + sophia.height) / TILE_SIZE; i++)
	{
		if (isSolid_Area3((sophia.x + sophia.width + 4) / TILE_SIZE, i))
		{
			return true;
		}
	}
	return false;
}
bool MAP::sophia_collide_left(SOPHIA sophia)
{
	for (int i = (sophia.y + sophia.height / 2) / TILE_SIZE; i <= (sophia.y + sophia.height) / TILE_SIZE; i++)
	{
		if (isSolid_Area3((sophia.x - 4) / TILE_SIZE, i))
		{
			return true;
		}
	}
	return false;
}
bool MAP::sophia_collide_up(SOPHIA sophia)
{
	for (int j = sophia.x / TILE_SIZE; j <= (sophia.x + sophia.width) / TILE_SIZE; j++)
	{
		if (isSolid_Area3(j, sophia.y / TILE_SIZE))
		{
			return true;
		}
	}
	return false;
}
bool MAP::sophia_collide_down(SOPHIA sophia)
{
	for (int j = sophia.x / TILE_SIZE; j <= (sophia.x + sophia.width) / TILE_SIZE; j++)
	{
		if (isSolid_Area3(j, (sophia.y + 8 + sophia.height) / TILE_SIZE))
		{
			return true;
		}
	}
	return false;
}

bool MAP::sophia_bullet_collide_right(BULLET bullet)
{
	for (int i = (bullet.y + bullet.height / 2) / TILE_SIZE; i <= (bullet.y + bullet.height) / TILE_SIZE; i++)
	{
		if (isSolid_Area3((bullet.x + bullet.width) / TILE_SIZE, i))
		{
			return true;
		}
	}
	return false;
}
bool MAP::sophia_bullet_collide_left(BULLET bullet)
{
	for (int i = (bullet.y + bullet.height / 2) / TILE_SIZE; i <= (bullet.y + bullet.height) / TILE_SIZE; i++)
	{
		if (isSolid_Area3((bullet.x) / TILE_SIZE, i))
		{
			return true;
		}
	}
	return false;
}
bool MAP::sophia_bullet_collide_up(BULLET bullet)
{
	for (int j = bullet.x / TILE_SIZE; j <= (bullet.x + bullet.width) / TILE_SIZE; j++)
	{
		if (isSolid_Area3(j, bullet.y / TILE_SIZE))
		{
			return true;
		}
	}
	return false;
}

bool MAP::sophia_collide_tele1(SOPHIA sophia)
{
	if (sophia.x < 64 && sophia.y > 736)
		return true;
	return false;
}
bool MAP::sophia_collide_tele2(SOPHIA sophia)
{
	if (sophia.x > 2464 && sophia.y > 768)
		return true;
	return false;
}
bool MAP::sophia_collide_tele3(SOPHIA sophia)
{
	if (sophia.x > 384 && sophia.y > 320)
		return true;
	return false;
}
