#include "GameEngine.h"
#include "Player.h"
#include "Wall.h"


GameEngine::GameEngine() : m_physic_engine(&this->m_entity_engine)
{
	this->window = nullptr;
	std::shared_ptr<Entity> player = std::make_shared<Player>();
	this->m_entity_engine.AddEntity(player);
	this->m_camera.SetEntityToFollow(player);

	for (int i = 0; i < 100; i++) {
		std::shared_ptr<Wall> wall = std::make_shared<Wall>();
		wall->GetComponents()->GetComponent<PhysicComponent>()->GetRigidBody()->SetPosition(sf::Vector2f(i * 256, 0));
		this->m_entity_engine.AddEntity(wall);
	}
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
	int frames = 0;
	float frameTime = 0;
	while (this->window->isOpen())
	{
		frames++;
		this->EventUpdate();
		float dt = clock.restart().asSeconds();
		frameTime += dt;
		if (frameTime > 1)
		{
			std::cout << frames << std::endl;
			frameTime = 0;
			frames = 0;
		}
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
	this->m_physic_engine.Update(dt);
	this->m_entity_engine.Update(dt);
}

void GameEngine::EventUpdate()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->window->close();
		if (event.type == sf::Event::MouseButtonReleased)
			this->m_camera.AddCameraShake(1);
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