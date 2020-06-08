#include "GameEngine.h"
#include "Player.h"


GameEngine::GameEngine()
{
	this->window = nullptr;
	std::shared_ptr<Entity> player = std::make_shared<Player>();
	this->m_entity_engine.AddEntity(player);
	this->m_camera.SetEntityToFollow(player);
}


GameEngine::~GameEngine()
{
}

void GameEngine::SetWindow(sf::RenderWindow& window)
{
	this->window = &window;
}

sf::RenderWindow* GameEngine::GetWindow()
{
	return this->window;
}

void GameEngine::StartGameLoop()
{
	sf::Clock clock;
	while (this->window->isOpen())
	{
		this->EventUpdate();
		float dt = clock.restart().asSeconds();
		this->Update(dt);
		this->Draw(dt);
	}
}

void GameEngine::Draw(float dt)
{
	this->window->clear();
	this->m_camera.Update(dt);
	this->m_camera.SetViewToTarget(*this->window);//set the view to the window
	this->m_entity_engine.Draw(*this->window);//draw all the entities to the window;
	this->m_light_engine.Draw(*this->window);//draw all lights
	this->window->display();
}

void GameEngine::Update(float dt)
{
	this->m_entity_engine.Update(dt);
}

void GameEngine::EventUpdate()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->window->close();
	}
}

LightEngine* GameEngine::GetLightEngine()
{
	return &this->m_light_engine;
}

EntityEngine* GameEngine::GetEntityEngine()
{
	return &this->m_entity_engine;
}