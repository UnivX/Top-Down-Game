#include "Wall.h"



Wall::Wall()
{
	sprite = sf::Sprite(global_textures.wall_texture, sf::IntRect(0, 0, 256, 256));
	this->m_name = "Wall";
	this->m_physic_component = new PhysicComponent();
	this->m_physic_component->CreateNewRigidBody();
	this->m_physic_component->GetRigidBody()->SetStatic();
	//this->m_physic_component->GetRigidBody()->SetDynamic();
	//this->m_physic_component->GetRigidBody()->SetMass(1);
	this->m_physic_component->GetRigidBody()->SetFriction(150);

	Collider collider;
	collider.GenerateAABBCollider(sf::Vector2f(256, 48));
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
	this->m_physic_component->getColliders()[0][0].SetPosition(this->position + sf::Vector2f(0,256-48));

	this->UpdateZ();
}

void Wall::Draw(sf::RenderTarget& target)
{
	this->sprite.setPosition(this->position);
	target.draw(this->sprite);
}

void Wall::UpdateZ()
{
	this->z = this->position.y + 256;
}

