#pragma once
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include "EntityEngine.h"
#include "PhysicEngine.h"
#include "GlobalVariables.h"
#include "Camera.h"
/*
TODO: fare tutto + descrizione

*/

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void SetWindow(sf::RenderWindow& window);
	sf::RenderWindow* GetWindow();
	void StartGameLoop();
	LightEngine* GetLightEngine();
	EntityEngine* GetEntityEngine();
private:

	void Draw(float dt);
	void Update(float dt);
	void EventUpdate();

	PhysicEngine m_physic_engine;
	EntityEngine m_entity_engine;
	LightEngine m_light_engine;
	Camera m_camera;
	sf::RenderWindow* window;
};

#endif // !GAME_ENGINE_H