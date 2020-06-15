#pragma once
#ifndef COLLISIONS_H
#define COLLISIONS_H
#include <SFML/Graphics.hpp>
#include <functional>

struct Hit {
	float overlap;
	sf::Vector2f normal;
	bool collide;
};

class AabbCollider {
public:
	AabbCollider();
	AabbCollider(float w, float h);

	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();

	void SetSize(sf::Vector2f size);
	sf::Vector2f GetSize();

private:
	sf::Vector2f size, position;
};

class SatCollider {
public:
	SatCollider();
	SatCollider(std::vector<sf::Vector2f> points);

	void CreateFromPoints(std::vector<sf::Vector2f> points);

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f vec);

	std::vector<std::pair<sf::Vector2f, sf::Vector2f>>* GetEdges();
private:
	sf::Vector2f m_position;
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> m_edges;

};

enum ColliderType {
	SAT,
	AABB,
	NONE
};

class Collider {
public:
	Collider();
	void GenerateAABBCollider(sf::Vector2f size);
	void GenerateSATCollider(std::vector<sf::Vector2f> points);

	ColliderType GetColliderType();
	SatCollider* GetSatCollider();
	AabbCollider* GetAABBCollider();
	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();

	bool IsPhysic();
	void SetIsPhysic(bool val);
	std::function<void(Collider*, Hit)> OnCollisionFunction;
private:
	bool m_is_physic;
	ColliderType m_type;
	SatCollider m_satCollider;
	AabbCollider m_aabbCollider;
	sf::Vector2f centroid;
	sf::Vector2f m_position;
};

std::pair<Hit, Hit> ResolveAABB(AabbCollider& collider1, AabbCollider& collider2);
std::pair<Hit, Hit> ResolveSAT(SatCollider& collider1, SatCollider& collider2);
//la fase larga e stretta sono già integrate
std::pair<Hit, Hit> ResolveColliderCollision(Collider& collider1, Collider& collider2);

#endif // !COLLISIONS_H

