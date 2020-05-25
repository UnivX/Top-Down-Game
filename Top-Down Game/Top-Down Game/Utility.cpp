#include "Utility.h"


float conversion_factor = 30.f;

void InitVectors(float _conversion_factor)
{
	conversion_factor = _conversion_factor;
}


float NormalizeAngle(float x) {
	x = fmod(x + PI, 2* PI);
	if (x < 0)
		x += 2* PI;
	return x - PI;
}

sf::Vector2f Normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

sf::Vector2f rotate_point(sf::Vector2f center, sf::Vector2f point, float radians)
{
	float s = sin(radians);
	float c = cos(radians);

	// translate point back to origin:
	point.x -= center.x;
	point.y -= center.y;

	// rotate point
	float xnew = point.x * c - point.y * s;
	float ynew = point.x * s + point.y * c;

	// translate point back:
	point.x = xnew + center.x;
	point.y = ynew + center.y;
	return point;
}