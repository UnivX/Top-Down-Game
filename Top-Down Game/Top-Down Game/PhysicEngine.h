#pragma once
#ifndef PHYSIC_ENGINE
#define PHYSIC_ENGINE
#include "EntityEngine.h"
#include "Collisions.h"

class PhysicEngine
{
public:
	PhysicEngine(EntityEngine* engine);
	~PhysicEngine();
	void Update(float dt);
private:
	EntityEngine* entityEnginePtr;

};

#endif // !PHYSIC_ENGINE