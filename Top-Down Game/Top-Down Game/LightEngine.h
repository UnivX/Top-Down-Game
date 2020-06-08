#pragma once
#ifndef LIGHTENGINE_H
#define LIGHT_ENGINE_H

#define SHADOW_LENGHT 2000.f
#include <SFML/Graphics.hpp>
#include <iostream>

/*
Descrizione
La LightMesh è una mesh che viene usata per calcolare le luci, è importante che la mesh coincidi il più possibile con lo sprite, la classe rappresenta un polygono e non una serie di lati non consecutivi
nell costruttore bisogna inserire una lista che rappresentano i punti di un poligono

La LightPoint è la rappresentazione di una luce che verra poi renderizata

LightEngine: è la classe che gestisce tutte e due le classi al di sopra sia per la memoria sia per il rendering, la classe gestisce anche la view del target, per sapere la poszione

NOTA:
la classe light point pre-renderizza la texture(a partire della vertex shader) della luce immagazinandola in memoria
*/

struct Edge {
	sf::Vector2f* p1, * p2;
};

typedef sf::Rect<float> AABB;

class LightMesh {
public:
	LightMesh(std::vector<sf::Vector2f> points);
	void Render(sf::RenderTarget& target);
	void SetRadians(float radians);
	AABB GetCollider();

	sf::Vector2f position;
	std::vector<Edge> edges;
	std::vector<sf::Vector2f> m_points;
	float radians;
	sf::Vector2f center;
private:
	AABB boxCollider;
};

class LightPoint {
public:
	LightPoint(sf::Color color, sf::Vector2f position, float radius, int8_t shadow_darkness = 100);
	LightPoint();
	~LightPoint();

	void SetShader(sf::Shader* shader);

	void GenerateLightSprite();

	void RenderLight();
	void RenderShadow(LightMesh& Mesh);
	void Draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
	AABB GetCollider();
	sf::Color color;
	sf::Vector2f pos;
	float radius;
private:
	bool spriteCreated;
	sf::Sprite lightCircleSprite;
	sf::CircleShape circle;
	sf::RenderTexture* lightTexture;
	sf::Shader* m_shader;
	AABB boxCollider;
	sf::Texture lightCircleTexture;
	int8_t shadow_darkness;
};

class LightEngine {
public:
	LightEngine();

	void AddMesh(LightMesh* Mesh);
	void AddLight(LightPoint* light);
	void RemoveLight(LightPoint* light);
	void RemoveMesh(LightMesh* Mesh);
	void Draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
	void DrawDebugInfo(sf::RenderTarget& target);
private:
	sf::Shader lightShader;
	std::vector<LightMesh*> entities;
	std::vector<LightPoint*> lights;
	sf::RenderTexture ambientalLightTexture;
	sf::Vector2f prevWindowSize;
};


#endif