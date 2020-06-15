#include "Wall.h"



Wall::Wall()
{
	this->m_rectangle = sf::RectangleShape(sf::Vector2f(50, 50));
	this->m_rectangle.setFillColor(sf::Color::Yellow);
	this->m_name = "Wall";
}


Wall::~Wall()
{
}

void Wall::Update(float deltaTime)
{
	this->UpdateZ();
}

void Wall::Draw(sf::RenderTarget& target)
{
	this->m_rectangle.setPosition(this->position);
	target.draw(this->m_rectangle);
}

void Wall::UpdateZ()
{
	this->z = this->position.y + this->m_size.y;
}

void Wall::SetSize(sf::Vector2f size)
{
	this->m_size = size;
	m_rectangle.setSize(size);
}
