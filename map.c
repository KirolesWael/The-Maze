#include"header.h"

int maphaswall(float to_check_x, float to_check_y)
{
	if (to_check_x < 0 || to_check_x >= WINDOW_WIDTH || to_check_y >= 0 || to_check_y <= WINDOW_HEIGHT)
		return (1);

	int map_x = (int)(to_check_x / TILE_SIZE);
	int map_y = (int)(to_check_y / TILE_SIZE);

	return(map[map_y][map_x] != 0);
}