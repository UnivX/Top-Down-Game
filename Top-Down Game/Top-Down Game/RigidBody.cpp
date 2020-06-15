#include "RigidBody.h"



RigidBody::RigidBody()
{
	this->acceleration = sf::Vector2f(0, 0);
	this->friction = 0;
	this->isStatic = false;
	this->position = sf::Vector2f(0, 0);
	this->m_mass = 1;
}


RigidBody::~RigidBody()
{
}


void RigidBody::OnCollision(Hit& data, sf::Vector2f accelerationSolution, float otherMass)
{
	if (this->isStatic)
		return;
	if(otherMass == INFINITY) //if other is static
		this->acceleration += accelerationSolution * 2.f;
	else
		this->acceleration += accelerationSolution;
	this->position += data.normal * data.overlap;
}

void RigidBody::Update(float dt)
{
	if (this->isStatic)
		return;

	this->position += this->acceleration / m_mass * dt;

	//update acceleration / friction
	float deltaFriction = this->friction * m_mass * dt;


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
	this->m_mass = INFINITY;
}

void RigidBody::SetDynamic()
{
	this->isStatic = false;
	this->m_mass = 1;
}

void RigidBody::SetMass(float mass)
{
	this->m_mass = mass;
}

float RigidBody::GetMass()
{
	return this->m_mass;
}
