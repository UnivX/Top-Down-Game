#include "LightEngine.h"
#include "Utility.h"
#include <string>
#include <fstream>
#define TO_STRING(x) #x

LightMesh::LightMesh(std::vector<sf::Vector2f> points) {
	this->radians = 0;
	//craeting all edges
	this->position = sf::Vector2f(0, 0);
	this->m_points = points;
	for (int i = 1; i < points.size(); i++) {
		this->edges.push_back(Edge{ &this->m_points[i - 1], &this->m_points[i] });
	}
	this->edges.push_back(Edge{ &this->m_points[points.size() - 1], &this->m_points[0] });

	//creating the box collider 
	sf::Vector2f size(0, 0);
	for (int i = 0; i < this->m_points.size(); i++) {
		if (this->m_points[i].x > size.x)
			size.x = this->m_points[i].x;
		if (this->m_points[i].y > size.y)
			size.y = this->m_points[i].y;
	}
	this->boxCollider.height = size.y;
	this->boxCollider.width = size.x;

	//get center
	sf::Vector2f centroid(0,0);
	for (int i = 0; i < this->m_points.size(); i++)
		centroid += this->m_points[i];

	centroid.x /= this->m_points.size();
	centroid.y /= this->m_points.size();
	this->center = centroid;
}

void LightMesh::Render(sf::RenderTarget& target) {
	//render all the edges
	for (int i = 0; i < edges.size(); i++) {
		sf::VertexArray vertexArray;
		vertexArray.resize(2);
		vertexArray.setPrimitiveType(sf::Lines);

		vertexArray[0].position = *this->edges[i].p1 + this->position;
		vertexArray[1].position = *this->edges[i].p2 + this->position;
		vertexArray[0].color = sf::Color::Red;
		vertexArray[1].color = sf::Color::Red;

		target.draw(vertexArray);
	}

}

void LightMesh::SetRadians(float radians)
{
	this->radians = radians;
}

AABB LightMesh::GetCollider() {
	this->boxCollider.left = this->position.x;
	this->boxCollider.top = this->position.y;
	return this->boxCollider;
}

LightPoint::LightPoint(sf::Color color, sf::Vector2f position, float radius, int8_t shadow_darkness) {
	this->shadow_darkness = shadow_darkness;
	this->color = color;
	this->radius = radius;
	this->pos = position;
	this->circle.setFillColor(this->color);
	this->lightTexture = new sf::RenderTexture;
	this->lightTexture->create(this->radius * 2, this->radius * 2);
	this->lightTexture->setSmooth(true);
	this->circle.setPosition(sf::Vector2f(0, 0));
	this->m_shader = nullptr;
	this->boxCollider = AABB(this->pos, sf::Vector2f(this->radius * 2, this->radius * 2));
	spriteCreated = false;
}
LightPoint::LightPoint() {
	this->shadow_darkness = 100;
	this->color = sf::Color::Yellow;
	this->radius = 100;
	this->pos = sf::Vector2f(0, 0);
	this->circle.setFillColor(this->color);
	this->lightTexture = new sf::RenderTexture;
	this->lightTexture->create(this->radius * 2, this->radius * 2);
	this->lightTexture->setSmooth(true);
	this->circle.setPosition(sf::Vector2f(0, 0));
	this->m_shader = nullptr;
	this->boxCollider = AABB(this->pos, sf::Vector2f(this->radius * 2, this->radius * 2));
	spriteCreated = false;
}

LightPoint::~LightPoint()
{
}

void LightPoint::SetShader(sf::Shader* shader) { this->m_shader = shader; this->GenerateLightSprite(); }

void LightPoint::GenerateLightSprite()
{
	sf::RenderTexture texture;
	texture.create(this->radius * 2, this->radius * 2);
	texture.setSmooth(true);
	this->circle.setRadius(this->radius);
	this->circle.setFillColor(this->color);
	if (this->m_shader != nullptr) {
		this->m_shader->setUniform("lightLocation", sf::Vector2f(this->radius, this->radius));
		this->m_shader->setUniform("lightColor", sf::Glsl::Vec4(this->color));
		this->m_shader->setUniform("radius", this->radius);
	}
	sf::RenderStates states;
	states.blendMode = sf::BlendMode(sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha);
	states.shader = this->m_shader;
	texture.draw(circle, states);
	lightCircleTexture = texture.getTexture();
	this->lightCircleSprite = sf::Sprite(lightCircleTexture);
	spriteCreated = true;
}
void LightPoint::RenderLight() {
	if (this->spriteCreated)
		this->lightTexture->draw(this->lightCircleSprite, sf::BlendMode(sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha));
	else
	{
		this->GenerateLightSprite();
		this->lightTexture->draw(this->lightCircleSprite, sf::BlendMode(sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha));
	}
}

void LightPoint::RenderShadow(LightMesh& Mesh) {
	sf::VertexArray vertexArray(sf::TriangleStrip, 4);
	vertexArray.resize(4);

	//set the color transparent
	for (int i = 0; i < 4; i++)
		vertexArray[i].color = sf::Color::Transparent;

	//render the shadow
	for (int i = 0; i < Mesh.edges.size(); i++) {
		sf::Vector2f* pos0 = &vertexArray[0].position;
		sf::Vector2f* pos1 = &vertexArray[1].position;
		sf::Vector2f* pos2 = &vertexArray[2].position;
		sf::Vector2f* pos3 = &vertexArray[3].position;

		//set the edges point as vertexes
		if (Mesh.radians != 0) {
			*pos0 = rotate_point(Mesh.center + Mesh.position, (*Mesh.edges[i].p1) + Mesh.position, Mesh.radians);
			*pos2 = rotate_point(Mesh.center + Mesh.position, (*Mesh.edges[i].p2) + Mesh.position, Mesh.radians);
		}
		else {
			sf::Vector2f lightPoin1Normal = Normalize(*pos0 - this->pos);
			sf::Vector2f lightPoin2Normal = Normalize(*pos2 - this->pos);
		}

		//get the direction betwen the light and and the vertexes of the edges
		sf::Vector2f lightPoin1Normal = Normalize(*pos0 - this->pos);
		sf::Vector2f lightPoin2Normal = Normalize(*pos2 - this->pos);

		//finding last 2 vertex
		*pos1 = *pos0 + (lightPoin1Normal * SHADOW_LENGHT);
		*pos3 = *pos2 + (lightPoin2Normal * SHADOW_LENGHT);

		//calc the local position of render texture
		*pos0 += -this->pos + sf::Vector2f(this->radius, this->radius);
		*pos1 += -this->pos + sf::Vector2f(this->radius, this->radius);
		*pos2 += -this->pos + sf::Vector2f(this->radius, this->radius);
		*pos3 += -this->pos + sf::Vector2f(this->radius, this->radius);
		this->lightTexture->draw(vertexArray, sf::BlendNone);
	}
}

void LightPoint::Draw(sf::RenderTarget& target, sf::RenderStates states) {
	//render the texture and draw to the target
	lightCircleSprite.setColor(sf::Color(255, 255, 255, 255 - this->shadow_darkness));
	this->lightTexture->draw(this->lightCircleSprite, sf::BlendMode(sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha));
	lightCircleSprite.setColor(sf::Color::White);

	this->lightTexture->display();
	sf::Sprite sprite(this->lightTexture->getTexture());
	sprite.setPosition(this->pos - sf::Vector2f(this->radius, this->radius));
	target.draw(sprite, states);
	this->lightTexture->clear(sf::Color::Transparent);
}

AABB LightPoint::GetCollider()
{
	this->boxCollider.left = this->pos.x - this->radius;
	this->boxCollider.top = this->pos.y - this->radius;
	return this->boxCollider;
}

LightEngine::LightEngine() {
	if (!sf::Shader::isAvailable())
	{
		std::cerr << "Error on set up of the LightEngine: shader not avaible\n";
	}

	std::ifstream f(std::string("light.frag"));
	if(!f.good())
		std::cerr << "Error on set up of the LightEngine: shader not found\n";


	if (!this->lightShader.loadFromFile("light.frag", sf::Shader::Fragment))
	{
		std::cerr << "Error on set up of the LightEngine: shader error\n";
	}
}

void LightEngine::AddMesh(LightMesh* Mesh) { this->entities.push_back(Mesh); }

void LightEngine::AddLight(LightPoint* light) {
	light->SetShader(&this->lightShader);
	this->lights.push_back(light);
}

void LightEngine::RemoveLight(LightPoint* light) {
	//search for a lightpoint in the list and remove it
	for (int i = 0; i < this->lights.size(); i++)
		if (light == this->lights[i])
			this->lights.erase(this->lights.begin() + i);
}

void LightEngine::RemoveMesh(LightMesh* Mesh) {
	//search for a Mesh in the list and remove it
	for (int i = 0; i < this->entities.size(); i++)
		if (Mesh == this->entities[i])
			this->entities.erase(this->entities.begin() + i);
}

void LightEngine::Draw(sf::RenderTarget & target, sf::RenderStates states) {
	sf::Vector2f viewCenter(target.getView().getCenter());
	sf::Vector2f viewSize(target.getView().getSize());
	AABB currentViewRect(viewCenter - viewSize / 2.f, viewSize);

	sf::Vector2f size = target.getView().getSize();

	//for every light
	for (int i = 0; i < this->lights.size(); i++) {
		//render the light
		LightPoint* lightPtr = this->lights[i];

		//if is in the view
		if (currentViewRect.intersects(lightPtr->GetCollider())) {


			lightPtr->RenderLight();

			//if a Mesh intersect with the light reder the shadow of the Mesh
			for (int e = 0; e < this->entities.size(); e++) {

				if (lightPtr->GetCollider().intersects(this->entities[e]->GetCollider()))
					lightPtr->RenderShadow(*this->entities[e]);
			}

			//draw the light
			lightPtr->Draw(target, states);
		}

	}
	prevWindowSize = size;
}

void LightEngine::DrawDebugInfo(sf::RenderTarget & target)
{
	//draw all the light's boxes
	sf::RectangleShape rect;
	for (int i = 0; i < this->entities.size(); i++) {
		AABB collider = this->entities[i]->GetCollider();
		rect.setPosition(sf::Vector2f(collider.left, collider.top));
		rect.setSize(sf::Vector2f(collider.width, collider.width));
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Green);
		rect.setOutlineThickness(1);
		target.draw(rect);
	}

	//draw all the Mesh's boxes
	for (int i = 0; i < this->lights.size(); i++) {
		AABB collider = this->lights[i]->GetCollider();
		rect.setPosition(sf::Vector2f(collider.left, collider.top));
		rect.setSize(sf::Vector2f(collider.width, collider.width));
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Green);
		rect.setOutlineThickness(1);
		target.draw(rect);
	}
}