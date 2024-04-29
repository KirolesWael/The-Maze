#include "defs.h"

ray_t	rays[NUM_RAYS];

bool	isRayFacingDown(float angle)
{
	return (angle > 0 && angle < PI);
}

bool	isRayFacingUp(float angle)
{
	return (!isRayFacingDown(angle));
}

bool	isRayFacingRight(float angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}

bool	isRayFacingLeft(float angle)
{
	return (!isRayFacingRight(angle));
}


void	castRay(float rayAngle, int stripId)
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;

	bool	foundHorzWallHit;
	float	horzWallHitX;
	float	horzWallHitY;
	int		horzWallTexture;

	float	nextHorzTouchX;
	float	nextHorzTouchY;

	float	horzHitDistance;

	bool	foundVertWallHit;
	float	vertWallHitX;
	float	vertWallHitY;
	int		vertWallTexture;

	float	nextVertTouchX;
	float	nextVertTouchY;

	float	vertHitDistance;
	

	float	xToCheck;
	float	yToCheck;

	normalizeAngle(&rayAngle);

	foundHorzWallHit = false;
	horzWallHitX = 0;
	horzWallHitY = 0;
	horzWallTexture = 0;

	
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown(rayAngle) ? TILE_SIZE : 0;

	
	xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

	
	ystep = TILE_SIZE;
	ystep *= isRayFacingUp(rayAngle) ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft(rayAngle) && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight(rayAngle) && xstep < 0) ? -1 : 1;

	nextHorzTouchX = xintercept;
	nextHorzTouchY = yintercept;

	
	while(isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		
		xToCheck = nextHorzTouchX;
		yToCheck = nextHorzTouchY + (isRayFacingUp(rayAngle) ? - 1 : 0);

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallTexture = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			foundHorzWallHit = true;
			break ;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}

	
	foundVertWallHit = false;
	vertWallHitX = 0;
	vertWallHitY = 0;
	vertWallTexture = 0;

	
	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += isRayFacingRight(rayAngle) ? TILE_SIZE : 0;

	
	yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

	
	xstep = TILE_SIZE;
	xstep *= isRayFacingLeft(rayAngle) ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (isRayFacingUp(rayAngle) && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown(rayAngle) && ystep < 0) ? -1 : 1;

	nextVertTouchX = xintercept;
	nextVertTouchY = yintercept;

	
	while(isInsideMap(nextVertTouchX, nextVertTouchY))
	{
		
		xToCheck = nextVertTouchX + (isRayFacingLeft(rayAngle) ? -1 : 0);
		yToCheck = nextVertTouchY;

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallTexture = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			foundVertWallHit = true;
			break ;
		}
		else
		{
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}

	
	horzHitDistance = foundHorzWallHit
	? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
	: FLT_MAX;
	vertHitDistance = foundVertWallHit
	? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
	: FLT_MAX;

	if (vertHitDistance < horzHitDistance)
	{
		rays[stripId].distance = vertHitDistance;
		rays[stripId].wallHitX = vertWallHitX;
		rays[stripId].wallHitY = vertWallHitY;
		rays[stripId].texture = vertWallTexture;
		rays[stripId].wasHitVertical = true;
		rays[stripId].rayAngle = rayAngle;
	}
	else
	{
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wallHitX = horzWallHitX;
		rays[stripId].wallHitY = horzWallHitY;
		rays[stripId].texture = horzWallTexture;
		rays[stripId].wasHitVertical = false;
		rays[stripId].rayAngle = rayAngle;
	}
}

void	castAllRays(void)
{
	float	rayAngle;
	float	distanceProjPlane;

	distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	
	for (int col = 0; col < NUM_RAYS; col++)
	{
		rayAngle = player.rotationAngle + atan((col - NUM_RAYS / 2) / distanceProjPlane);
		castRay(rayAngle, col);
	}
}

void	renderMapRays(void)
{
	for (int i = 0; i < NUM_RAYS; i += 50)
	{
		drawLine(
			player.x * MINIMAP_SCALE_FACTOR,
			player.y * MINIMAP_SCALE_FACTOR,
			rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
			rays[i].wallHitY * MINIMAP_SCALE_FACTOR,
			0xFF0000FF
		);
	}
}