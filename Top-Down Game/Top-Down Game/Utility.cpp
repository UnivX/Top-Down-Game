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

float dotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
	return vec1.x* vec2.x + vec1.y * vec2.y;
}

sf::Vector2f rotateVector90(const sf::Vector2f& vec)
{
	sf::Vector2f aVec = vec;
	sf::Vector2f NVec;
	NVec.x = aVec.x * 0 - aVec.y * 1;
	NVec.y = aVec.x * 1 + aVec.y * 0;

	return NVec;
}

float LenghtVector(const sf::Vector2f& vect1)
{
	return sqrt(pow(vect1.x, 2) + pow(vect1.y, 2));
}

sf::Vector2f DegreeToVector(float floatDegree)
{
	float radians = (floatDegree) * (PI / 180.0);
	return sf::Vector2f(cos(radians), sin(radians));
}