#pragma once
#ifndef ENTITY_ENGINE_H
#define ENTITY_ENGINE_H
#include "Entity.h"
#include "GlobalVariables.h"



/*
Descrizione:
la classe entityEngine gestisce tutte le istanze di una entità, le istanze entity sono incapsulate in shared_ptr, solo l'entity engine ne detiene owning,
tutte le altre classi faranno riferimento tramite un weak_ptr.

prima che un entità possa essere inserita in un chunk deve essere inserita prima nel entity engine
per semplicità le entità sono divisi in chunk in modo da suddividere le aree di gioco e mettere in suspend eliminare e riprendere una porzione di gioco come una stanza



*/

class Chunk;

class EntityEngine
{
public:
	EntityEngine();
	~EntityEngine();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderTarget& target);

	virtual void DeleteChunk(std::shared_ptr<Chunk> chunk);
	virtual void AddChunk(std::shared_ptr<Chunk> chunk);
	std::vector<std::shared_ptr<Chunk>>* GetChunkList();

	virtual void AddEntity(std::shared_ptr<Entity> entity);

protected:
	GlobalEntityList entities;
	std::vector<std::shared_ptr<Chunk>> chunks;
};

class Chunk {
public:
	Chunk(EntityEngine* engine);
	virtual ~Chunk();

	virtual void AddExistingEntity(std::weak_ptr<Entity> entity);
	virtual void NewEntity(std::shared_ptr<Entity> entity);
	virtual void RemoveEntity(std::weak_ptr<Entity> entityRawPtr);

	virtual void DeleteChunk();
	virtual void Suspend();
	virtual void Resume();

	LocalEntityList* getEntity
protected:
	bool suspended;
	LocalEntityList entities;
	EntityEngine* main_entity_engine;
};

#endif // !ENTITY_ENGINE_H