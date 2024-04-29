#include"header.h"

bool isfaceingdown(float angle)
{
	return (angle > 0 && angle < PI);
}

bool isfaceingright(float angle)
{
	return (angle < 0.5 * PI || angle> 1.5 * PI);
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}
