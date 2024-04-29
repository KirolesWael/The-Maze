#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <limits.h>
#include"upng.h"




#define PI 3.14159265
#define TWO_PI 6.28318530

#define TILE_SIZE 64

#define NUM_TEXTURES 14
#define NUM_SPRITES 6

#define MINIMAP_SCALE_FACTOR 0.2

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define FOV_ANGLE (60 * (PI / 180))

#define NUM_RAYS WINDOW_WIDTH

#define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))

#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20

typedef uint32_t color_t;

typedef struct {
	float	x;
	float	y;
	float	width;
	float	height;
	int		turnDirection; // -1 for left, +1 for right
	int		walkDirection; // -1 for back, +1 for front
	float	rotationAngle;
	float	walkSpeed;
	float	turnSpeed;
}player_t;

extern player_t player;

typedef struct	{
	float	rayAngle;
	float	wallHitX;
	float	wallHitY;
	float	distance;
	bool	wasHitVertical;
	int		texture;
}			ray_t;

extern ray_t	rays[NUM_RAYS];

typedef struct
{
	float	x;
	float	y;
	float	distance;
	float	angle;
	bool	visible;
	int		texture;
}	sprite_t;

upng_t	*textures[NUM_TEXTURES];




/*graphics.c*/
bool	initializeWindow(void);
void	destroyWindow(void);
void	clearColorBuffer(color_t color);
void	renderColorBuffer(void);
void	drawPixel(int x, int y, color_t color);
void	drawRect(int x, int y, int width, int height, color_t color);
void	drawLine(int x0, int y0, int x1, int y1, color_t color);


/*map.c*/
bool	mapHasWallAt(float x, float y);
bool	isInsideMap(float x, float y);
void	renderMapGrid(void);
int		getMapAt(int i, int j);

/*player.c*/
void	movePlayer(float deltaTime);
void	renderMapPlayer(void);

/*ray.c*/
bool	isRayFacingUp(float angle);
bool	isRayFacingDown(float angle);
bool	isRayFacingLeft(float angle);
bool	isRayFacingRight(float angle);
void	castAllRays(void);
void	castRay(float rayAngle, int stripId);
void	renderMapRays(void);

/*sprites.c*/
void	renderSpriteProjection(void);
void	renderMapSprites(void);

/*textures.c*/
void	loadTextures();
void	freeTextures();

/*utils.c*/
void	normalizeAngle(float *angle);
int		distanceBetweenPoints(float x1, float y1, float x2, float y2);

/*wall.c*/
void	renderWallProjection(void);
void	changeColorIntensity(color_t *color, float factor);



#endif