#include "EntityEngine.h"
#include "GameEngine.h"
/*
for (auto t = this->entities.begin(); t != this->entities.end(); ++t) {
		ptr = t->lock();
		if (ptr->IsDeleted())
			deletedEntities.push_back(t);
	}

	auto it = std::find_if(this->entities.begin(), this->entities.end(), [=](const std::weak_ptr<Entity> & val) {
		if (val.lock().get() == entityRawPtr)
			return true;
		return false;
		});
	it->lock()->Delete(); //delete the boy
	this->entities.erase(it); //remove the deleted boy from list

*/

EntityEngine::EntityEngine()
{
}


EntityEngine::~EntityEngine()
{
}

void EntityEngine::Update(float dt)
{
	std::vector<GlobalEntityList::iterator> deletedEntities;

	for (GlobalEntityList::iterator t = this->entities.begin(); t != this->entities.end(); ++t) {
		if ((*t)->IsDeleted()) {
			deletedEntities.push_back(t);
			break;
		}
		if(!(*t)->IsSuspended())
			(*t)->Update(dt);
	}
}

void EntityEngine::Draw(sf::RenderTarget& target)
{
	for (GlobalEntityList::iterator t = this->entities.begin(); t != this->entities.end(); ++t)
		if (!(*t)->IsSuspended())
			(*t)->Draw(target);
}

void EntityEngine::DeleteChunk(std::shared_ptr<Chunk> chunk)
{
	auto it = std::find_if(this->chunks.begin(), this->chunks.end(), [&](const std::shared_ptr<Chunk> & val) {
		
		if (val.get() == chunk.get())
			return true;
		return false;
		});

	(*it)->DeleteChunk();
	this->chunks.erase(it); 
}

void EntityEngine::AddChunk(std::shared_ptr<Chunk> chunk)
{
	this->chunks.push_back(chunk);
}

std::vector<std::shared_ptr<Chunk>>* EntityEngine::GetChunkList()
{
	return &this->chunks;
}

void EntityEngine::AddEntity(std::shared_ptr<Entity> entity)
{
	this->entities.push_back(entity);
}

Chunk::Chunk(EntityEngine* engine)
{
	this->main_entity_engine = engine;
}

Chunk::~Chunk()
{

}

void Chunk::AddExistingEntity(std::weak_ptr<Entity> entity)
{
}

void Chunk::NewEntity(std::shared_ptr<Entity> entity)
{
	this->entities.push_back(entity);
}

void Chunk::RemoveEntity(std::weak_ptr<Entity> entityRawPtr)
{
	auto it = std::find_if(this->entities.begin(), this->entities.end(), [=](const std::weak_ptr<Entity> & val) {
		if (val.expired() || entityRawPtr.expired())
			return false;

		if (val.lock().get() == entityRawPtr.lock().get())
			return true;

		return false;
		});
	this->entities.erase(it); //remove the boy from list
}

void Chunk::DeleteChunk()
{
	for (LocalEntityList::iterator t = this->entities.begin(); t != this->entities.end(); ++t)
		if (!t->expired() && (!t->lock()->IsDeleted()))
			t->lock()->Delete();
}

void Chunk::Suspend()
{
	for (LocalEntityList::iterator t = this->entities.begin(); t != this->entities.end(); ++t)
		if (!t->expired())
			t->lock()->Suspend();
}

void Chunk::Resume()
{
	for (LocalEntityList::iterator t = this->entities.begin(); t != this->entities.end(); ++t)
		if (!t->expired())
			t->lock()->Resume();
}
