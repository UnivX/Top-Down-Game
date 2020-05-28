#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "Entity.h"
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
	void SetViewToTarget(sf::RenderTarget& target);

	void AddCameraShake(float force);
	void SetCameraShake(float force);

	void SetEntityToFollow(std::weak_ptr<Entity> entity);

	void SetTraumaReducing(float tr);
	float GetTraumaReducing();

	float GetMaxAngleShaking();
	void SetMaxAngleShaking(float maxAngle);

	float GetMaxOffSetShaking();
	void SetMaxOffSetShaking(float offset);

	float GetCameraSmoothness();
	void SetCameraSmoothness(float smoothness);

	float GetCameraAngle();
	void SetCameraAngle(float angle);

	sf::Vector2f GetCameraPositionOffSet();
	void SetCameraPositionOffSet(sf::Vector2f offset);

	float GetCameraTrauma();
private:
	sf::Vector2f m_pos;
	ShakingData ComputeCameraShake(float dt);
	std::weak_ptr<Entity> followed_entity;
	sf::View view;
	float m_angle;
	float m_trauma;
	float trauma_reducing;
	float m_camera_smoothness;
	sf::Vector2f m_camera_position_offset;

	float maxAngleShaking;
	float maxOffSetShaking;
};

#endif