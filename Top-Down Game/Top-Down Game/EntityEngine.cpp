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
	//sorting the vector in base of the z value
	std::sort(this->entities.begin(), this->entities.end(), [](const std::shared_ptr<Entity> & entity1, const std::shared_ptr<Entity> & entity2) {
		return (entity1->GetZ() < entity2->GetZ());
		});

	for (GlobalEntityList::iterator t = this->entities.begin(); t != this->entities.end(); ++t)
		if (!(*t)->IsSuspended())
			(*t)->Draw(target);
}

void EntityEngine::AddEntity(std::shared_ptr<Entity> entity)
{
	entity->SetEntityEngine(this);
	this->entities.push_back(entity);
}

GlobalEntityList* EntityEngine::GetEntityList()
{
	return &this->entities;
}
