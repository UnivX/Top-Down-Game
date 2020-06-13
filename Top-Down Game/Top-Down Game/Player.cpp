#include "Player.h"
#include "GameEngine.h"


Player::Player()
{
	sprite = sf::Sprite(global_textures.player_texture, sf::IntRect(0, 0, 128, 128));
	this->m_name = "Player";
	this->velocity = 300;
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//std::cout << "position: " << this->position.x << ", " << this->position.y << std::endl;
	this->sprite.setPosition(this->position);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->position.x -= velocity * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->position.x += velocity * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->position.y -= velocity * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->position.y += velocity * deltaTime;

	this->UpdateZ();
}

void Player::Draw(sf::RenderTarget& target)
{
	target.draw(this->sprite);

}

void Player::UpdateZ()
{
	this->z = this->position.y + 128;
}
