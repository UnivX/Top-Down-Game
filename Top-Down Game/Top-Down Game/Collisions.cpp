#include "Collisions.h"
#include "Utility.h"

AabbCollider::AabbCollider()
{
	this->size = sf::Vector2f(0, 0);
	this->position = sf::Vector2f(0, 0);
}

AabbCollider::AabbCollider(float w, float h)
{
	this->size = sf::Vector2f(w, h);
	this->position = sf::Vector2f(0, 0);
}

void AabbCollider::SetPosition(sf::Vector2f pos)
{
	this->position = pos;
}

sf::Vector2f AabbCollider::GetPosition()
{
	return this->position;
}

void AabbCollider::SetSize(sf::Vector2f size)
{
	this->size = size;
}

sf::Vector2f AabbCollider::GetSize()
{
	return this->size;
}

SatCollider::SatCollider()
{
	this->m_position = sf::Vector2f(0, 0);
}

SatCollider::SatCollider(std::vector<sf::Vector2f> points)
{
	this->m_position = sf::Vector2f(0, 0);
	this->CreateFromPoints(points);
}

void SatCollider::CreateFromPoints(std::vector<sf::Vector2f> points)
{
	this->m_edges.resize(points.size());
	for (int i = 1; i < points.size(); i++) {
		this->m_edges[i - 1].first = points[i - 1];
		this->m_edges[i - 1].second = points[i];
	}
	this->m_edges[this->m_edges.size() - 1].first = points[points.size() - 1];
	this->m_edges[this->m_edges.size() - 1].second = points[0];
}

sf::Vector2f SatCollider::GetPosition()
{
	return this->m_position;
}

void SatCollider::SetPosition(sf::Vector2f vec)
{
	this->m_position = vec;
}

std::vector<std::pair<sf::Vector2f, sf::Vector2f>>* SatCollider::GetEdges()
{
	return &this->m_edges;
}


Collider::Collider()
{
	this->m_type = ColliderType::NONE;
	this->m_aabbCollider.SetPosition(sf::Vector2f(0, 0));
	this->m_satCollider.SetPosition(sf::Vector2f(0, 0));
	this->centroid = sf::Vector2f(0, 0);
	this->m_position = sf::Vector2f(0, 0);
	this->m_is_physic = false;
	this->OnCollisionFunction = nullptr;
}

void Collider::GenerateAABBCollider(sf::Vector2f size)
{
	this->m_type = ColliderType::AABB;
	this->m_aabbCollider.SetSize(size);
	this->m_satCollider.CreateFromPoints({ sf::Vector2f(0,0), sf::Vector2f(size.x,0), size, sf::Vector2f(0,size.y) });
	this->centroid = size / 2.f;
}

void Collider::GenerateSATCollider(std::vector<sf::Vector2f> points)
{
	this->m_type = ColliderType::SAT;
	this->centroid = sf::Vector2f(0, 0);
	sf::Vector2f bounds;

	for (int i = 0; i < points.size(); i++) {
		this->centroid += points[i];
		bounds.x = std::max(points[i].x, bounds.x);
		bounds.y = std::max(points[i].y, bounds.y);
	}
	this->centroid /= float(points.size());
	this->m_satCollider.CreateFromPoints(points);
	this->m_aabbCollider.SetSize(bounds);
}

ColliderType Collider::GetColliderType()
{
	return this->m_type;
}

SatCollider* Collider::GetSatCollider()
{
	return &this->m_satCollider;
}

AabbCollider* Collider::GetAABBCollider()
{
	return &this->m_aabbCollider;
}

void Collider::SetPosition(sf::Vector2f pos)
{
	this->m_position = pos;
	this->m_aabbCollider.SetPosition(pos);
	this->m_satCollider.SetPosition(pos);
}

sf::Vector2f Collider::GetPosition()
{
	return this->m_position;
}

bool Collider::IsPhysic()
{
	return this->m_is_physic;
}

void Collider::SetIsPhysic(bool val)
{
	this->m_is_physic = val;
}

void Collider::SetFunctionOnCollide(void(*function)(Collider*, Hit))
{
	this->OnCollisionFunction = function;
}

std::function<void(Collider*, Hit)> Collider::GetOnCollisionFunction()
{
	return this->OnCollisionFunction;
}

//need rework
std::pair<Hit, Hit> ResolveAABB(AabbCollider& collider1, AabbCollider& collider2)
{
	Hit hit1, hit2;
	hit1.collide = false;
	hit2.collide = false;
	sf::Vector2f bestAxis;
	float bestMag = INFINITY;

	//first axis (1,0)
	float min1 = collider1.GetPosition().x;
	float min2 = collider2.GetPosition().x;

	float max1 = collider1.GetPosition().x + collider1.GetSize().x;
	float max2 = collider2.GetPosition().x + collider2.GetSize().x;

	
	if (max1 >= min2 && max2 >= min1) {
		//calcola se è più corta la soluzione normale o invertita
		float mag = max1 - min2;
		float invMag = max2 - min1;
		float localBestMag = std::min(mag, invMag);
		if (localBestMag < bestMag)
		{
			bestMag = localBestMag;
			bestAxis = sf::Vector2f(1, 0);
			if (bestMag == invMag)
				bestAxis *= -1.f;
		}
	}
	//se non intersecano finisci
	else 
		return std::pair<Hit, Hit>(hit1, hit2);

	//second axis (0,1)
	min1 = collider1.GetPosition().y;
	min2 = collider2.GetPosition().y;

	max1 = collider1.GetPosition().y + collider1.GetSize().y;
	max2 = collider2.GetPosition().y + collider2.GetSize().y;


	if (max1 >= min2 && max2 >= min1) {
		//calcola se è più corta la soluzione normale o invertita
		float mag = max1 - min2;
		float invMag = max2 - min1;
		float localBestMag = std::min(mag, invMag);
		if (localBestMag < bestMag)
		{
			bestMag = localBestMag;
			bestAxis = sf::Vector2f(0, 1);
			if (bestMag == invMag)
				bestAxis *= -1.f;
		}
	}
	//se non intersecano finisci
	else
		return std::pair<Hit, Hit>(hit1, hit2);
	hit1.collide = true;
	hit2.collide = true;
	hit1.normal = -bestAxis;
	hit2.normal = bestAxis;
	hit1.overlap = bestMag;
	hit2.overlap = bestMag;

	return std::pair<Hit, Hit>(hit1, hit2);
}

//best mag bug
std::pair<Hit, Hit> ResolveSAT(SatCollider& collider1, SatCollider& collider2)
{
	Hit hit1, hit2;
	hit1.collide = false;
	hit2.collide = false;
	sf::Vector2f accAxis;
	sf::Vector2f bestAxis;

	float bestMag = INFINITY;

	float min1 = INFINITY;
	float min2 = INFINITY;
	float max1 = -INFINITY;
	float max2 = -INFINITY;
	float temp = 0;
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>>* edges1 = collider1.GetEdges();
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>>* edges2 = collider1.GetEdges();

	//calc all collider1 axis
	for (int i = 0; i < edges1->size(); i++) {
		accAxis = rotateVector90(Normalize(edges1[0][i].second - edges1[0][i].first));//get edge normal roteted

		for (int j = 0; j < edges1->size(); j++) {
			temp = dotProduct((*edges1)[j].first + collider1.GetPosition(), accAxis); // punto priettato sull asse
			min1 = std::min(min1, temp);
			max1 = std::max(max1, temp);
		}

		for (int j = 0; j < edges2->size(); j++) {
			temp = dotProduct((*edges2)[j].first + collider2.GetPosition(), accAxis); // punto priettato sull asse
			min2 = std::min(min2, temp);
			max2 = std::max(max2, temp);
		}

		//se i due segmenti mono dimesionali si intersecano
		if (max1 >= min2 && max2 >= min1) {
			//calcola se è più corta la soluzione normale o invertita
			float mag = max1 - min2;
			float invMag = max2 - min1;
			float bestMag = std::min(mag, invMag);
			bestAxis = accAxis;

			if (bestMag == invMag)
				bestAxis *= -1.f;
		}
		else //se non intersecano finisci
			return std::pair<Hit, Hit>(hit1, hit2);
	}

	//calc all collider2 axis
	for (int i = 0; i < edges2->size(); i++) {
		accAxis = rotateVector90(Normalize(edges2[0][i].second - edges2[0][i].first));//get edge normal roteted

		for (int j = 0; j < edges1->size(); j++) {
			temp = dotProduct((*edges1)[j].first + collider1.GetPosition(), accAxis); // punto priettato sull asse
			min1 = std::min(min1, temp);
			max1 = std::max(max1, temp);
		}

		for (int j = 0; j < edges2->size(); j++) {
			temp = dotProduct((*edges2)[j].first + collider2.GetPosition(), accAxis); // punto priettato sull asse
			min2 = std::min(min2, temp);
			max2 = std::max(max2, temp);
		}

		//se i due segmenti mono dimesionali si intersecano
		if (max1 >= min2 && max2 >= min1) {
			//calcola se è più corta la soluzione normale o invertita
			float mag = max1 - min2;
			float invMag = max2 - min1;
			float bestMag = std::min(mag, invMag);
			bestAxis = accAxis;

			if (bestMag == invMag)
				bestAxis *= -1.f;
		}
		else //se non intersecano finisci
			return std::pair<Hit, Hit>(hit1, hit2);
	}
	
	hit1.collide = true;
	hit1.overlap = bestMag;
	hit1.normal = -rotateVector90(bestAxis);

	hit2.collide = true;
	hit2.overlap = bestMag;
	hit2.normal = rotateVector90(bestAxis);

	return std::pair<Hit, Hit>(hit1, hit2);
}

std::pair<Hit, Hit> ResolveColliderCollision(Collider& collider1, Collider& collider2)
{

	if (collider1.GetColliderType() == ColliderType::NONE || collider2.GetColliderType() == ColliderType::NONE)//se i collider non sono stati creati ritrna falso
		return std::pair<Hit, Hit>(Hit{ 0,sf::Vector2f(0,0),false }, Hit{ 0,sf::Vector2f(0,0),false });

	//se almeno uno è sat
	if (collider1.GetColliderType() == ColliderType::SAT || collider2.GetColliderType() == ColliderType::SAT) {
		if (ResolveAABB(*collider1.GetAABBCollider(), *collider2.GetAABBCollider()).first.collide) // se aabb collidono
			return ResolveSAT(*collider1.GetSatCollider(), *collider2.GetSatCollider());//ritorna il valore della collisione sat
	}
	else
		return ResolveAABB(*collider1.GetAABBCollider(), *collider2.GetAABBCollider());

	return std::pair<Hit, Hit>(Hit{ 0,sf::Vector2f(0,0),false }, Hit{ 0,sf::Vector2f(0,0),false });
}
