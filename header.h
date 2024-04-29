#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <limits.h>
#include<math.h>
#include<stdint.h>


static int game_is_running = false;


#define MAP_WIDTH 13
#define MAP_HEIGHT 20
#define TILE_SIZE 64
#define WINDOW_WIDTH (MAP_WIDTH * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_HEIGHT * TILE_SIZE)
#define PI 3.141592653589793
#define DELTA_ANGLE WINDOW_WIDTH/player.fov




static const int map[MAP_WIDTH][MAP_HEIGHT] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1},
{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
{1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1},
{1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1},
{1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
{1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };


struct player_t
{
	float x;
	float y;
	float angle;
	float speed;
	float ang_speed;
	float fov;
	float raduis;
}player;


struct ray_t
{
	float ray_angle;
	float wall_hit_x;
	float wall_hit_y;
	float distance;
	bool washitvert;
	int wallcontent;
}rays[WINDOW_WIDTH];

struct sdl_sys
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* color_buffer_texture;
	uint32_t* color_buffers;
}sdl_r;



int initialize_window(void);
void process_input(void);
void setup(void);
void update(void);
void render(void);
void destroy_window(void);

void draw_3d_rays();
void cast_ray(float ray_angle, int strip_id);
void horzIntersection(float rayAngle);
void vertIntersection(float ray_angle);


bool isfaceingdown(float angle);
bool isfaceingright(float angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);


int maphaswall(float to_check_x, float to_check_y);

#endif // !HEADER_H
