#include "PhysicEngine.h"
#include "PhysicComponent.h"
#include "Utility.h"


PhysicEngine::PhysicEngine(EntityEngine* engine)
{
	this->entityEnginePtr = engine;
}

PhysicEngine::~PhysicEngine()
{
}

void PhysicEngine::Update(float dt)
{
	for (GlobalEntityList::iterator i = this->entityEnginePtr->GetEntityList()->begin(); i != this->entityEnginePtr->GetEntityList()->end(); ++i)
		for (GlobalEntityList::iterator j = this->entityEnginePtr->GetEntityList()->begin(); j != this->entityEnginePtr->GetEntityList()->end(); ++j) {

			PhysicComponent* component1 = i->get()->GetComponents()->GetComponent<PhysicComponent>();
			PhysicComponent* component2 = j->get()->GetComponents()->GetComponent<PhysicComponent>();

			

			if (*j == *i || component1 == nullptr || component2 == nullptr)
				continue;

			bool haveRigidBody = component1->GetRigidBody() != nullptr && component1->GetRigidBody();

			if (haveRigidBody && component1->GetRigidBody()->GetIsStatic() && component2->GetRigidBody()->GetIsStatic()) // se sono tutti e due statici non vengono calcolate le collisioni
				continue;
			if (component1->GetCollidersSize() == 1 && component2->GetCollidersSize() == 1) {
				Collider* collider1 = &(*component1->getColliders())[0];
				Collider* collider2 = &(*component2->getColliders())[0];


				std::pair<Hit, Hit> hits = ResolveColliderCollision(*collider1, *collider2);
				//if collide
				if (hits.first.collide) {
					if (collider1->GetOnCollisionFunction() != nullptr)
						collider1->GetOnCollisionFunction()(collider1, hits.first);

					if (collider2->GetOnCollisionFunction() != nullptr)
						collider2->GetOnCollisionFunction()(collider2, hits.second);

					//if is physic
					if (haveRigidBody && collider1->IsPhysic() && collider2->IsPhysic()) {
						sf::Vector2f deltaAcc = (component2->GetRigidBody()->GetAcceleration() - component1->GetRigidBody()->GetAcceleration()) / 2.f;
						component1->GetRigidBody()->OnCollision(hits.first, -hits.first.normal * dotProduct(-hits.first.normal, deltaAcc), component2->GetRigidBody()->GetMass());
						component2->GetRigidBody()->OnCollision(hits.second, -hits.second.normal * dotProduct(-hits.second.normal, -deltaAcc), component1->GetRigidBody()->GetMass());
					}
				}
				continue;
			}
			

			for (int e = 0; e < component1->getColliders()->size(); e++)
				for (int e2 = 0; e2 < component2->getColliders()->size(); e2++) {
					Collider* collider1 = &(*component1->getColliders())[0];
					Collider* collider2 = &(*component2->getColliders())[0];


					std::pair<Hit, Hit> hits = ResolveColliderCollision(*collider1, *collider2);
					//if collide
					if (hits.first.collide) {
						if (collider1->GetOnCollisionFunction() != nullptr)
							collider1->GetOnCollisionFunction()(collider1, hits.first);

						if (collider2->GetOnCollisionFunction() != nullptr)
							collider2->GetOnCollisionFunction()(collider2, hits.second);

						//if is physic
						if (haveRigidBody && collider1->IsPhysic() && collider2->IsPhysic()) {
							sf::Vector2f deltaAcc = (component2->GetRigidBody()->GetAcceleration() - component1->GetRigidBody()->GetAcceleration()) / 2.f;
							component1->GetRigidBody()->OnCollision(hits.first, -hits.first.normal * dotProduct(-hits.first.normal, deltaAcc), component2->GetRigidBody()->GetMass());
							component2->GetRigidBody()->OnCollision(hits.second, -hits.second.normal * dotProduct(-hits.second.normal, -deltaAcc), component1->GetRigidBody()->GetMass());
						}
					}
				}
		}
}



