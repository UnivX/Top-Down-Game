#pragma once
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include "EntityEngine.h"
#include "GlobalVariables.h"
/*
TODO: fare tutto + descrizione

*/

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
private:
	EntityEngine m_entity_engine;
};

#endif // !GAME_ENGINE_H