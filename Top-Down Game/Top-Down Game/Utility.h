#pragma once
#ifndef UTILITY_H
#define UTILITY_H
#include <SFML/Graphics.hpp>


/*
Descrizione:
ci sono per lo più funzioni matematiche e altre funzioni utili un po' ovunque

*/

#define PI 3.14159265359
extern float conversion_factor;
void InitVectors(float _conversion_factor);

float NormalizeAngle(float x);

sf::Vector2f Normalize(const sf::Vector2f& source);

sf::Vector2f rotate_point(sf::Vector2f center, sf::Vector2f point, float radians);

#endif // !UTILITY_H