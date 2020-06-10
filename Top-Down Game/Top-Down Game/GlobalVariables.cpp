#include "GlobalVariables.h"
#include "GameEngine.h"
#include <iostream>

GameEngine* gameEngine = new GameEngine();
TextureList global_textures;

void TextureList::LoadData()
{
	std::cout << "loading textures\n";
	this->player_texture.loadFromFile("wizard.png");
	this->wall_texture.loadFromFile("wall.png");
}
