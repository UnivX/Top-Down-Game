#include "PhysicComponent.h"



PhysicComponent::PhysicComponent()
{
	this->rigidBody = nullptr;
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
}
