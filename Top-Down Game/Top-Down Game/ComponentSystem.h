#pragma once
#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H
#include <string>
#include <vector>
 /*
 Descrizione:
 definizioni delle classi che creano il component system, ogni entit� ha un istanza di questa classe
 essenzialmente � una lista di classi chiamate componenti a cui si pu� accedere in base al tipo(all tipo di classe derivata dalla classe base component)
 se nella lista non � presente un istanza della classe selezionata ritorner� un nullptr

 */

//baseclass
class Component
{
public:
	Component();
	virtual ~Component();
};

class ComponentSystem
{
public:
	ComponentSystem();
	~ComponentSystem();
	template<class T>
	T* GetComponent();
	std::vector<Component*> components;
};


template<class T>
inline T* ComponentSystem::GetComponent()
{
	T* ptr;
	int i = 0; 
	while (i < this->components.size()) {
		ptr = dynamic_cast<T*>(this->components[i]);

		if (ptr != NULL)
			return ptr;
		i++;
	}
	return nullptr;
}

#endif