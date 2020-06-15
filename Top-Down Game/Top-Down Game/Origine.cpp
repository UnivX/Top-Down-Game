#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComponentSystem.h"
#include "GenericTypeList.h"
#include "GlobalVariables.h"
#include "GameEngine.h"

/*
TIPS:
FOR RANDOM SPAWNS USE GenericTypeList
-movere la camera e dare un feedback quando si elimina un nemico insieme a altri effetti
-craere proiettili grossi, espolisioni grosse
-effetti grossi
-non muovere troppo la camera
-creare una specie di distruttibilità del nemico
-giocare con la posizione della camera
-far si che il gioctore si movi con fluidità e che sia responsivo come effetti visivi nei dash
-far si che i power up passivi e attivi interagiscano tra di loro in modo indiretto
-pensare ad un tipo di avanzamento che non modifichi la difficolta del gioco
-il dash è solo un aumento repentino della velocità, non un movimento statico

TODO:

-aggiungere al rigidbody il calcolo della massa
- creare il physic engine con il risolutore delle collisioni
- debbugare rigidbody
- debugare il modulo collision
- Create Event system like signal and slot for static entities in the map, for more interactivity
- creare un event system per il motore di gioco in cui ogni entittà può richiamare o aggiungere un nuovo evento
-creare una gui dinamica e fresh

*/

/*
IMPORTANT: GLOBAL VARIABLES CONTAIN THE MAIN ENGINE ONBJECT

*/

/*
Ogni file di intestazione contiene una piccola descrizione di ciò che contiene
*/

class MyComponent : public Component{
public:
	MyComponent() {
		std::cout << "test constructor\n";
	}

	~MyComponent() {
		std::cout << "test deconstructor\n";
	}

	void test() {
		std::cout << "test\n";
	}
};

class MyComponent2 : public Component {
public:
	int i;
	MyComponent2() {
		i = 2;
		std::cout << "test2 constructor\n";
	}

	~MyComponent2() {
		std::cout << "test2 deconstructor\n";
	}

	void test2() {
		std::cout << "test" << i << "\n";
	}
};

void CodeTesting(){
	std::cout << "GenericTypeList use:\n";
	GenericTypeList<Component> typelist;
	typelist.AddType<MyComponent2>();
	typelist.AddType<MyComponent>();
	Component* base = typelist.Instantiate(0);
	delete base;
	base = typelist.Instantiate(1);
	delete base;



	std::cout << "\nComponentSystem use:\n";
	ComponentSystem cp;
	cp.components.emplace_back(new MyComponent2());
	cp.components.emplace_back(new MyComponent());

	cp.GetComponent<MyComponent2>()->test2();
	cp.GetComponent<MyComponent2>()->i = 34;

	cp.GetComponent<MyComponent2>()->test2();
	cp.GetComponent<MyComponent>()->test();
}

int main()
{
	global_textures.LoadData();
	//game engine is an global varbiale declared in GlobalVaribles.h
	CodeTesting();

	sf::RenderWindow window(sf::VideoMode(200, 200), "OMG IT WORKS!");
	gameEngine->SetWindow(window);
	gameEngine->StartGameLoop();

	
	delete gameEngine;
	return 0;
}