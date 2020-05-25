#include "LightMeshComponent.h"



LightMeshComponent::LightMeshComponent()
{
	m_light_engine = nullptr;
}

LightMeshComponent::LightMeshComponent(LightEngine* engine)
{
	this->m_light_engine = engine;
}


LightMeshComponent::~LightMeshComponent()
{
	if (this->m_light_engine == nullptr && this->MeshList.size() != 0) 
		throw "FATAL ERROR: fuck mate this->m_light_engine in LightMeshComponent::~LightMeshComponent is nullptr, i'm sorry for the bad programming :(";

	for (int i = 0; i < this->MeshList.size(); i++) {
		this->m_light_engine->RemoveMesh(this->MeshList[i]);
		delete this->MeshList[i];
		this->MeshList[i] = nullptr;
	}
}
