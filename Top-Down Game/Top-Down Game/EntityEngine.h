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


class EntityEngine
{
public:
	EntityEngine();
	~EntityEngine();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderTarget& target);

	virtual void AddEntity(std::shared_ptr<Entity> entity);
	GlobalEntityList* GetEntityList();
protected:
	GlobalEntityList entities;
};


#endif // !ENTITY_ENGINE_H