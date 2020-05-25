#pragma once
#ifndef LIGHT_MESH_COMPONENT_H
#define LIGHT_MESH_COMPONENT_H

#include "ComponentSystem.h"
#include "LightEngine.h"

class LightMeshComponent :
	public Component
{
public:
	LightMeshComponent();
	LightMeshComponent(LightEngine* engine);
	~LightMeshComponent();
	std::vector<LightMesh*> MeshList;
private:
	LightEngine* m_light_engine;
};

#endif // !LIGHT_MESH_COMPONENT_H
