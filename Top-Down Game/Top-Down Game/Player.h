#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	void Update(float deltaTime) override;
	void Draw(sf::RenderTarget& target) override;
	void UpdateZ() override;
private:
	float velocity;
	sf::Sprite sprite;
};

#endif // !PLAYER_H
