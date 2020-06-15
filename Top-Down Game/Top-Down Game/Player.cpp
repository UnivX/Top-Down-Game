#include "Player.h"
#include "GameEngine.h"


Player::Player()
{
	sprite = sf::Sprite(global_textures.player_texture, sf::IntRect(0, 0, 128, 128));
	this->m_name = "Player";
	this->velocity = 800;
	this->m_physic_component = new PhysicComponent();
	this->m_physic_component->CreateNewRigidBody();
	this->m_physic_component->GetRigidBody()->SetDynamic();
	this->m_physic_component->GetRigidBody()->SetMass(1);
	this->m_physic_component->GetRigidBody()->SetFriction(150);

	Collider collider;
	collider.GenerateAABBCollider(sf::Vector2f(128, 128));
	collider.SetIsPhysic(true);

	this->m_physic_component->AddNewCollider(collider);
	this->m_components.components.push_back(this->m_physic_component);
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//std::cout << "position: " << this->position.x << ", " << this->position.y << std::endl;
	this->sprite.setPosition(this->position);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->m_physic_component->GetRigidBody()->AddAcceleration(sf::Vector2f(-velocity * deltaTime, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->m_physic_component->GetRigidBody()->AddAcceleration(sf::Vector2f(velocity * deltaTime, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->m_physic_component->GetRigidBody()->AddAcceleration(sf::Vector2f(0, -velocity * deltaTime));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->m_physic_component->GetRigidBody()->AddAcceleration(sf::Vector2f(0, velocity * deltaTime));

	this->m_physic_component->GetRigidBody()->Update(deltaTime);
	this->position = this->m_physic_component->GetRigidBody()->GetPosition();
	this->m_physic_component->getColliders()[0][0].SetPosition(this->position);

	this->UpdateZ();
}

void Player::Draw(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	sf::RectangleShape rect(sf::Vector2f(128, 128));
	rect.setOutlineColor(sf::Color::Red);
	rect.setFillColor(sf::Color::Transparent);
	rect.setPosition(this->m_physic_component->getColliders()[0][0].GetPosition());
	rect.setOutlineThickness(1);
	target.draw(rect);
}

void Player::UpdateZ()
{
	this->z = this->position.y + 128;
}