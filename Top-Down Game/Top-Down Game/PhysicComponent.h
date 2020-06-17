#pragma once
#ifndef PHYSIC_COMPONENT_H
#define PHYSIC_COMPONENT_H
#include "ComponentSystem.h"
#include "Collisions.h"
#include "RigidBody.h"

class PhysicComponent :
	public Component
{
public:
	PhysicComponent();
	~PhysicComponent();

	RigidBody* GetRigidBody();
	std::vector<Collider>* getColliders();

	void CreateNewRigidBody();
	void AddNewCollider(Collider& collider);
	int GetCollidersSize();
protected:
	int m_colliders_size;
	RigidBody* rigidBody;
	std::vector<Collider> colliders;
};

#endif // !PHYSIC_COMPONENT_H
