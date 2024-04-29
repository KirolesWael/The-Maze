#include"header.h"



static bool foundHorzWallHit, foundVertWallHit;
static float horzWallHitX, horzWallHitY, vertWallHitX, vertWallHitY;
static int horzWallContent, vertWallContent;

void draw_3d_rays()
{
	float ray_angle;
	int strip_id;

	ray_angle = player.angle - player.fov / 2;

	for (strip_id = 0; strip_id < WINDOW_WIDTH; strip_id++)
	{
		cast_ray(ray_angle, strip_id);
		ray_angle += player.fov / WINDOW_WIDTH;
	}
}

void cast_ray(float ray_angle, int strip_id)
{
	float horizdist, verticdist;

	if (ray_angle < 0)
		ray_angle += 2 * PI;
	else if (ray_angle > 2 * PI)
		ray_angle -= 2 * PI;

	horzIntersection(ray_angle);
	vertIntersection(ray_angle);

	horizdist = foundHorzWallHit
		? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
		: 10000000;
	verticdist = foundVertWallHit
		? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
		: 100000000;

	if (verticdist < horizdist)
	{
		rays[strip_id].distance = verticdist;
		rays[strip_id].wall_hit_x = vertWallHitX;
		rays[strip_id].wall_hit_y = vertWallHitY;
		rays[strip_id].wallcontent = vertWallContent;
		rays[strip_id].washitvert = true;
		rays[strip_id].ray_angle = ray_angle;
	}
	else
	{
		rays[strip_id].distance = horizdist;
		rays[strip_id].wall_hit_x = horzWallHitX;
		rays[strip_id].wall_hit_y = horzWallHitY;
		rays[strip_id].wallcontent = horzWallContent;
		rays[strip_id].washitvert = false;
		rays[strip_id].ray_angle = ray_angle;
	}

}

void horzIntersection(float ray_angle)
{
	float horiztouchx, horiztouchy, xintercept, yintercept, xstep, ystep;

	foundHorzWallHit = false;
	horzWallHitX = horzWallHitY = horzWallContent = 0;

	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept = isfaceingdown(ray_angle) ? TILE_SIZE : 0;

	xintercept = player.x + (yintercept - player.y) / tan(ray_angle);

	ystep = TILE_SIZE;
	ystep *= (!isfaceingdown(ray_angle)) ? -1 : 1;
	xstep = TILE_SIZE / tan(ray_angle);
	xstep *= (!isfaceingright(ray_angle) && xstep > 0) ? -1 : 1;
	xstep *= (isfaceingright(ray_angle) && xstep < 0) ? -1 : 1;
	horiztouchx = xintercept;
	horiztouchy = yintercept;

	while ((horiztouchx >= 0 && horiztouchx <= MAP_HEIGHT * TILE_SIZE &&
		horiztouchy >= 0 && horiztouchy <= MAP_WIDTH * TILE_SIZE))
	{
		float x_to_check = horiztouchx;
		float y_to_check = horiztouchy + (!isfaceingdown(ray_angle) ? -1 : 0);
		if (maphaswall(x_to_check, y_to_check)) 
		{
			horzWallHitX = horiztouchx;
			horzWallHitY = horiztouchy;
			horzWallContent = map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			foundHorzWallHit = true;
			break;
		}
		horzWallHitX += xstep;
		horzWallHitY += ystep;
	}
}

void vertIntersection(float ray_angle)
{
	float verttouchx, verttouchy, xintercept, yintercept, xstep, ystep;

	foundVertWallHit = false;
	vertWallHitX = vertWallHitY = vertWallContent = 0;

	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept = isfaceingright(ray_angle) ? TILE_SIZE : 0;

	yintercept = player.y + (xintercept - player.x) * tan(ray_angle);

	xstep = TILE_SIZE;
	xstep *= (!isfaceingright(ray_angle)) ? -1 : 1;
	ystep = TILE_SIZE * tan(ray_angle);
	ystep *= (!isfaceingdown(ray_angle) && ystep > 0) ? -1 : 1;
	xstep *= (isfaceingdown(ray_angle) && ystep < 0) ? -1 : 1;
	verttouchx = xintercept;
	verttouchy = yintercept;

	while ((verttouchx >= 0 && verttouchx <= MAP_HEIGHT * TILE_SIZE &&
		verttouchy >= 0 && verttouchy <= MAP_WIDTH * TILE_SIZE))
	{
		float x_to_check = verttouchx + (!isfaceingright(ray_angle) ? -1 : 0);
		float y_to_check = verttouchy;
		if (maphaswall(x_to_check, y_to_check))
		{
			vertWallHitX = verttouchx;
			vertWallHitY = verttouchy;
			vertWallContent = map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			foundVertWallHit = true;
			break;
		}
		vertWallHitX += xstep;
		vertWallHitY += ystep;
	}
}