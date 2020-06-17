#include "PhysicComponent.h"



PhysicComponent::PhysicComponent()
{
	this->rigidBody = nullptr;
	this->m_colliders_size = 0;
}


PhysicComponent::~PhysicComponent()
{
}

RigidBody* PhysicComponent::GetRigidBody()
{
	return this->rigidBody;
}

std::vector<Collider>* PhysicComponent::getColliders()
{
	return &this->colliders;
}

void PhysicComponent::CreateNewRigidBody()
{
	this->rigidBody = new RigidBody();
}

void PhysicComponent::AddNewCollider(Collider& collider)
{
	this->colliders.push_back(collider);
	this->m_colliders_size++;
}

int PhysicComponent::GetCollidersSize()
{
	return this->m_colliders_size;
}
