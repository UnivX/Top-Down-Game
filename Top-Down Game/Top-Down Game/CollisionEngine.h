#pragma once
#ifndef COLLISION_ENGINE_H
#define COLLISION_ENGINE_H
#include "GlobalVariables.h"
#include "MultiThreading.h"
#include "EntityEngine.h"
#include "ComponentSystem.h"
#include "Utility.h"
#include <memory>

//la solution1 è il vettore che risolve la collisione se applicato al primo collider, per risolvere applicandolo al collider2 : collider2.pos += -solution1;

struct SatEdge {
	SatEdge();
	SatEdge(sf::Vector2f p1, sf::Vector2f p2);
	void CalcolateNormal();

	sf::Vector2f point1, point2, normal, normalRot90;
};

class SatCollisionMesh {
public:
	SatCollisionMesh();
	SatCollisionMesh(std::vector<sf::Vector2f> points);

	~SatCollisionMesh();

	void CreateFromPoints(std::vector<sf::Vector2f>& points);

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f vec);


	int GetEdgesSize();
	int GetPointsSize();

	SatEdge* GetEdges();
	sf::Vector2f* GetPoints();

private:
	sf::Vector2f pos;

	int edges_size;
	int points_size;
	SatEdge* edges;
	sf::Vector2f* points;
};

class SatTask : public Task {
public:
	void Do() override;
	//input vars
	SatCollisionMesh* collisionMesh1, * collisionMesh2;

	//output vars
	sf::Vector2f solution1;
	bool collide;
};


class AABB {
public:
	AABB();
	AABB(float w, float h);

	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();

	void SetSize(sf::Vector2f size);
	sf::Vector2f GetSize();

private:
	sf::Vector2f size, position;
};

class AABBTask : public Task {
public:
	void Do() override;
	//input vars
	AABB* aabb1, * aabb2;

	//output vars
	sf::Vector2f solution1;
	bool collide;
};

class Collider {
public:
	Collider();
	void GenerateFromAABB(sf::Vector2f size);
	void GenerateFromSATMesh(std::vector<sf::Vector2f> points);
	void UpdatePositions();

	AABB aabb;
	SatCollisionMesh m_sat_mesh;

	bool isAABB;
	sf::Vector2f pos;
};

#endif //!COLLISION_ENGINE_H