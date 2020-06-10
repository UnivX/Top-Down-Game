#include "Entity.h"
#include <assert.h>


Entity::Entity()
{
	this->deleted = false;
	this->z = 0;
	this->position = sf::Vector2f(0, 0);
	this->m_entity_engine = nullptr;
	this->suspended = false;
}

Entity::Entity(EntityEngine* entity_engine)
{
	this->deleted = false;
	this->z = 0;
	this->position = sf::Vector2f(0, 0);
	this->m_entity_engine = entity_engine;
	this->suspended = false;
}

void Entity::SetEntityEngine(EntityEngine* entity_engine)
{
	this->m_entity_engine = entity_engine;
}


Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{
}

void Entity::UpdateZ()
{
	this->z = this->position.y;
}

void Entity::Draw(sf::RenderTarget& target)
{
}

ComponentSystem* Entity::GetComponents()
{
	return &this->m_components;
}

sf::Vector2f Entity::GetPosition()
{
	return this->position;
}

void Entity::SetPosition(sf::Vector2f vector)
{
	this->position = vector;
}

float Entity::GetZ()
{
	return this->z;
}

void Entity::SetZ(float z)
{
	this->z = z;
}

void Entity::Delete()
{
	this->deleted = true;
}

bool Entity::IsDeleted()
{
	return this->deleted;
}

bool Entity::IsSuspended()
{
	return this->suspended;
}

void Entity::Suspend()
{
	this->suspended = true;
}

void Entity::Resume()
{
	this->suspended = false;
}

std::string Entity::GetName()
{
#ifdef _DEBUG
	assert(this->m_name != "");
#endif // _DEBUGG
	return this->m_name;
}
