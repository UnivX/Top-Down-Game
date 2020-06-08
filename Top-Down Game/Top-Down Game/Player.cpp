#include "Player.h"
#include "GameEngine.h"


Player::Player()
{
	this->m_rectangle = sf::RectangleShape(sf::Vector2f(50, 50));
	this->m_rectangle.setFillColor(sf::Color::Green);
	this->m_name = "Player";
	this->velocity = 100;
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	std::cout << "position: " << this->position.x << ", " << this->position.y << std::endl;
	this->m_rectangle.setPosition(this->position);

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
	target.draw(this->m_rectangle);

}
