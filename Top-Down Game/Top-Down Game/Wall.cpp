#include "Wall.h"



Wall::Wall()
{
	this->m_rectangle = sf::RectangleShape(sf::Vector2f(50, 50));
	this->m_rectangle.setFillColor(sf::Color::Yellow);
	this->m_name = "Wall";
	this->m_physic_component = new PhysicComponent();
	this->m_physic_component->CreateNewRigidBody();
	this->m_physic_component->GetRigidBody()->SetDynamic();
	this->m_physic_component->GetRigidBody()->SetMass(1);
	this->m_physic_component->GetRigidBody()->SetFriction(150);

	Collider collider;
	collider.GenerateAABBCollider(sf::Vector2f(100, 100));
	collider.SetIsPhysic(true);

	this->m_physic_component->AddNewCollider(collider);
	this->m_components.components.push_back(this->m_physic_component);
}


Wall::~Wall()
{
}

void Wall::Update(float deltaTime)
{
	this->m_physic_component->GetRigidBody()->Update(deltaTime);
	this->position = this->m_physic_component->GetRigidBody()->GetPosition();
	this->m_physic_component->getColliders()[0][0].SetPosition(this->position - sf::Vector2f(12, 12));

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
