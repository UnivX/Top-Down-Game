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
-creare una specie di distruttibilit� del nemico
-giocare con la posizione della camera
-far si che il gioctore si movi con fluidit� e che sia responsivo come effetti visivi nei dash
-far si che i power up passivi e attivi interagiscano tra di loro in modo indiretto
-pensare ad un tipo di avanzamento che non modifichi la difficolta del gioco
-il dash � solo un aumento repentino della velocit�, non un movimento statico

TODO:
-finire il game engine e l'entity engine
-commentare un po' il codice


- Create Event system like signal and slot for static entities in the map, for mare interactivity
- creare un event system per il motore di gioco in cui ogni entitt� pu� richiamare o aggiungere un nuovo evento
-creare una gui dinamica e fresh

*/

/*
IMPORTANT: GLOBAL VARIABLES CONTAIN THE MAIN ENGINE ONJECT

*/

/*
Ogni file di intestazione contiene una piccola descrizione di ci� che contiene
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
	//inside there is the game engine
	GameEngine* gameEnginePtr = gameEngine;

	CodeTesting();

	sf::RenderWindow window(sf::VideoMode(200, 200), "OMG IT WORKS!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}