#include "ComponentSystem.h"



ComponentSystem::ComponentSystem()
{
}


ComponentSystem::~ComponentSystem()
{
	for (int i = 0; i < this->components.size(); i++)
		delete this->components[i];
	this->components.clear();
}

Component::Component()
{
}

Component::~Component()
{
}

