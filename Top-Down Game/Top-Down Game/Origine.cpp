#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComponentSystem.h"
#include "GenericTypeList.h"

/*
TIPS:
FOR RANDOM SPAWNS USE GenericTypeList
jj


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