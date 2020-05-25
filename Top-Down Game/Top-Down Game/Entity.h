#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include "ComponentSystem.h"
#include "LightEngine.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Entity;

typedef void(*NewEntityFunctionPtr)(std::shared_ptr<Entity>);
typedef std::vector<std::weak_ptr<Entity>> LocalEntityList;
typedef std::vector<std::shared_ptr<Entity>> GlobalEntityList;

class Entity
{
public:
	Entity();
	Entity(NewEntityFunctionPtr new_entity_ptr, LocalEntityList* local_list);
	void SetNewEntityPtr(NewEntityFunctionPtr new_entity_ptr);
	void SetLocalEntityList(LocalEntityList* local_list);
	virtual ~Entity();
	virtual void Update(float deltaTime);
	virtual void Draw(sf::RenderTarget& target);
	ComponentSystem* GetComponents();

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f vector);
	float GetZ();
	void SetZ(float z);
	
	void Delete();
	bool IsDeleted();
protected:
	ComponentSystem m_components;
	bool deleted;
	float z;
	sf::Vector2f position;
	NewEntityFunctionPtr m_new_entity_ptr;
	LocalEntityList* m_local_list;
};
#endif // !ENTITY_H
