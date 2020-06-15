#pragma once
#ifndef WALL_H
#define WALL_H
#include "Entity.h"
#include "PhysicComponent.h"

class Wall : public Entity
{
public:
	Wall();
	~Wall();
	void Update(float deltaTime) override;
	void Draw(sf::RenderTarget& target) override;
	void UpdateZ() override;
	void SetSize(sf::Vector2f size);

private:
	sf::RectangleShape m_rectangle;
	sf::Vector2f m_size;
	PhysicComponent* m_physic_component;
};

#endif // !WALL_H
