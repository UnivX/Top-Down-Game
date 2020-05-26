#pragma once
#ifndef LIGHT_MESH_COMPONENT_H
#define LIGHT_MESH_COMPONENT_H

#include "ComponentSystem.h"
#include "LightEngine.h"

/*
Descrizione:
è il componente di un oggettoo che supporta il rendering della luce dinamica,
contiene una lista LightMesh per vedere in dettaglio la classe consultare il file LightEngine-h


*/

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
