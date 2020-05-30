#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include "ComponentSystem.h"
#include "LightEngine.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "GlobalVariables.h"

/*
Descrizione:
classe base di ogni oggetto presente a schermo che interagisce con la classe del giocatore
alla classe servono delle referenze alla lista locale delle entit�(la lista locale � per esmpio la lista di tutte le entit� in stanza)
la lista globale � la lista di tutte le entit� create anche se sono in modalit� di sospensione
quando l'entit� � in suspende non verra ne renderizata ne chiamata la funzione update che � il cuore della classe, rispamiando cos� prestazioni senza perdere i dati.
la classe deve avere un puntatore a una funzione che creer� una nuova entit� nella lista locale o nel chunk locale
La componente Z � la profondit�, che serve per ordinare le entit� per un rendering in base alla profondit�
la variabile m_name � il nome di sistema dell entit� caratteristica unica di ogni classe derivata dall classe base entity

SetNewEntityPtr
SetLocalEntityList
sono funzioni che DEVONO essere chiamate altrimenti potrebbero portare ad un malfunzionamento della classe
in alternativa si pu� utilizzare il costruttore 
Entity(NewEntityFunctionPtr new_entity_ptr, LocalEntityList* local_list)
per risolvere le dipendenze

*/

class Entity;

typedef void(*NewEntityFunctionPtr)(std::shared_ptr<Entity>);
typedef std::vector<std::weak_ptr<Entity>> LocalEntityList;
typedef std::vector<std::shared_ptr<Entity>> GlobalEntityList;

class Entity
{
public:
	Entity();
	Entity(NewEntityFunctionPtr new_entity_ptr, LocalEntityList* local_list);
	void SetNewEntityPtr(NewEntityFunctionPtr new_entity_ptr);
	void SetLocalEntityList(LocalEntityList* local_list);
	virtual ~Entity();
	virtual void Update(float deltaTime);
	virtual void Draw(sf::RenderTarget& target);
	ComponentSystem* GetComponents();

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f vector);
	float GetZ();
	void SetZ(float z);
	
	void Delete();
	bool IsDeleted();

	bool IsSuspended();
	void Suspend();
	void Resume();

	std::string GetName();
protected:
	ComponentSystem m_components;
	bool deleted;
	bool suspended;
	float z;			//depth
	std::string m_name;
	sf::Vector2f position;
	NewEntityFunctionPtr m_new_entity_ptr;
	LocalEntityList* m_local_list;
};
#endif // !ENTITY_H
