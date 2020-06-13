#include "RigidBody.h"



RigidBody::RigidBody()
{
	this->acceleration = sf::Vector2f(0, 0);
	this->friction = 0;
	this->isStatic = false;
	this->position = sf::Vector2f(0, 0);
}


RigidBody::~RigidBody()
{
}

void RigidBody::OnCollision(CollideInformation& data)
{
	this->acceleration = data.accelerationSolution;
	this->position = data.translationSolution;
}

void RigidBody::Update(float dt)
{
	this->position += this->acceleration * dt;

	//update acceleration / friction
	float deltaFriction = this->friction * dt;


	//update x acceleration
	if (this->acceleration.x > 0) {
		if (this->acceleration.x - deltaFriction < 0)
			this->acceleration.x = 0;
		else
			this->acceleration.x -= deltaFriction;
	}
	
	else //(this->acceleration.x < 0)
	{
		if (this->acceleration.x + deltaFriction > 0)
			this->acceleration.x = 0;
		else
			this->acceleration.x += deltaFriction;
	}


	//update y acceleration
	if (this->acceleration.y > 0) {
		if (this->acceleration.y - deltaFriction < 0)
			this->acceleration.y = 0;
		else
			this->acceleration.y -= deltaFriction;
	}

	else //(this->acceleration.x < 0)
	{
		if (this->acceleration.y + deltaFriction > 0)
			this->acceleration.y = 0;
		else
			this->acceleration.y += deltaFriction;
	}

}

sf::Vector2f RigidBody::GetAcceleration()
{
	return this->acceleration;
}

void RigidBody::SetAcceleration(sf::Vector2f acc)
{
	this->acceleration = acc;
}

void RigidBody::AddAcceleration(sf::Vector2f acc)
{
	this->acceleration += acc;
}

sf::Vector2f RigidBody::GetPosition()
{
	return this->position;
}

void RigidBody::SetPosition(sf::Vector2f pos)
{
	this->position = pos;
}

float RigidBody::GetFriction()
{
	return this->friction;
}

void RigidBody::SetFriction(float dg)
{
	this->friction = dg;
}

bool RigidBody::GetIsStatic()
{
	return this->isStatic;
}

bool RigidBody::GetIsDynamic()
{
	return !this->isStatic;
}

void RigidBody::SetStatic()
{
	this->isStatic = true;
}

void RigidBody::SetDynamic()
{
	this->isStatic = false;
}
