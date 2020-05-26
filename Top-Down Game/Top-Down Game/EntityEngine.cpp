#include "EntityEngine.h"



EntityEngine::EntityEngine()
{
}


EntityEngine::~EntityEngine()
{
}

void EntityEngine::UpdateChunks(float dt)
{
}

void EntityEngine::DrawChunks(sf::RenderTarget& target)
{
}

void EntityEngine::DeleteChunk(Chunk* chunk)
{
}

void EntityEngine::AddChunk(Chunk* chunk)
{
}

Chunk::Chunk()
{
}

Chunk::~Chunk()
{
}

void Chunk::Update(float dt)
{
}

void Chunk::Draw(sf::RenderTarget& target)
{
}

void Chunk::NewEntity(std::shared_ptr<Entity>)
{
}

void Chunk::Suspend()
{
}

void Chunk::Resume()
{
}
