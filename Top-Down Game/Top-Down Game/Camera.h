#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "Utility.h"
// TODO:
// AABB Collider
// Perlin Noise camera shaking

//maintain trauma level 0.1

struct ShakingData {
	sf::Vector2f transitional;
	float rotational;
};


class Camera
{
public:
	Camera();
	~Camera();
	void Update(float dt);
	void AddCameraShake(float force);
private:
	ShakingData ComputeCameraShake(float dt);
	sf::View view;
	float m_trauma;
	float trauma_reducing;

	float maxAngleShaking;
	float maxOffSetShaking;
};

#endif