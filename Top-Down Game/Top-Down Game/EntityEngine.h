#pragma once
#ifndef ENTITY_ENGINE_H
#define ENTITY_ENGINE_H
#include "Entity.h"
#include "GlobalVariables.h"


/*
Descrizione:
la classe entityEngine gestisce tutte le istanze di una entità, le istanze entity sono incapsulate in shared_ptr, solo l'entity engine ne detiene owning,
tutte le altre classi faranno riferimento tramite un weak_ptr.

per semplicità le entità sono divisi in chunk in modo da suddividere le aree di gioco e mettere in suspend eliminare e riprendere una porzione di gioco come una stanza


*/

class Chunk;

class EntityEngine
{
public:
	EntityEngine();
	~EntityEngine();
	virtual void UpdateChunks(float dt);
	virtual void DrawChunks(sf::RenderTarget& target);

	virtual void DeleteChunk(Chunk* chunk);
	virtual void AddChunk(Chunk* chunk);

protected:
	GlobalEntityList entities;
	std::vector<Chunk*> chunks;
};

class Chunk {
public:
	Chunk();
	virtual ~Chunk();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderTarget& target);
	virtual void NewEntity(std::shared_ptr<Entity>);
	virtual void Suspend();
	virtual void Resume();
protected:
	LocalEntityList entities;
	EntityEngine* main_entity_engine;
};

#endif // !ENTITY_ENGINE_H