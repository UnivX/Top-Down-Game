#pragma once
#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include <SFML/Graphics.hpp>

/*
Descrizione:
qui ci sono tutte le variabili globali a cui si possono fare riferimento da per tutto

*/
struct TextureList {
	void LoadData();
	sf::Texture player_texture;
	sf::Texture wall_texture;
};

class GameEngine;



extern TextureList global_textures;
extern GameEngine* gameEngine;

#endif // !GlobalVariables


