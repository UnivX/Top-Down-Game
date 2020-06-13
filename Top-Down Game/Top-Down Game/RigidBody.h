#pragma once
#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "CollisionEngine.h"

//TODO:
// implementazione della massa nei calcoli

class RigidBody
{
public:
	RigidBody();
	~RigidBody();

	void OnCollision(CollideInformation& data);
	void Update(float dt);

	sf::Vector2f GetAcceleration();
	void SetAcceleration(sf::Vector2f acc);
	void AddAcceleration(sf::Vector2f acc);


	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f pos);

	float GetFriction();
	void SetFriction(float dg);

	bool GetIsStatic();
	bool GetIsDynamic();

	void SetStatic();
	void SetDynamic();
private:
	sf::Vector2f position;
	sf::Vector2f acceleration;
	bool isStatic;
	float friction;
};

#endif // !RIGID_BODY_H
