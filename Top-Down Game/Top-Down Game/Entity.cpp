#include "Entity.h"
#include <assert.h>


Entity::Entity()
{
	this->deleted = false;
	this->m_new_entity_ptr = nullptr;
	this->z = 0;
	this->position = sf::Vector2f(0, 0);
	this->m_local_list = nullptr;
	this->suspended = false;
}

Entity::Entity(NewEntityFunctionPtr new_entity_ptr, LocalEntityList* local_list)
{
	this->m_local_list = local_list;
	this->m_new_entity_ptr = new_entity_ptr;
}


void Entity::SetNewEntityPtr(NewEntityFunctionPtr new_entity_ptr)
{
	this->m_new_entity_ptr = new_entity_ptr;
}

void Entity::SetLocalEntityList(LocalEntityList* local_list)
{
	this->m_local_list = local_list;
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{
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
