#include "CollisionEngine.h"




SatEdge::SatEdge()
{
	this->point1 = sf::Vector2f(0, 0);
	this->point2 = sf::Vector2f(0, 0);
}


SatEdge::SatEdge(sf::Vector2f p1, sf::Vector2f p2)
{
	this->point1 = p1;
	this->point2 = p2;
}

void SatEdge::CalcolateNormal()
{
	this->normal = Normalize(this->point2 - this->point1);
	this->normalRot90 = rotateVector90(this->normal);
}


SatCollisionMesh::SatCollisionMesh()
{
	this->pos = sf::Vector2f(0, 0);
	this->edges_size = 0;
	this->points_size = 0;
	this->edges = nullptr;
	this->points = nullptr;
}


SatCollisionMesh::SatCollisionMesh(std::vector<sf::Vector2f> points)
{
	this->pos = sf::Vector2f(0, 0);
	this->edges_size = 0;
	this->points_size = 0;
	this->edges = nullptr;
	this->points = nullptr;
	this->CreateFromPoints(points);
}


SatCollisionMesh::~SatCollisionMesh()
{
	if (this->edges != nullptr)
		free(this->edges);

	if (this->points != nullptr)
		free(this->points);

	this->edges = nullptr;
	this->points = nullptr;
}


void SatCollisionMesh::CreateFromPoints(std::vector<sf::Vector2f>& p)
{
	this->points = static_cast<sf::Vector2f*>(malloc(p.size() * sizeof(sf::Vector2f)));
	this->points_size = p.size();

	this->edges = static_cast<SatEdge*>(malloc(p.size() * sizeof(Edge)));
	this->edges_size = p.size();

	for (int i = 0; i < this->points_size; i++)
		this->points[i] = p[i];

	for (int i = 1; i < this->points_size; i++) {
		this->edges[i - 1].point1 = this->points[i - 1];
		this->edges[i - 1].point2 = this->points[i];
		this->edges[i - 1].CalcolateNormal();
	}

	//add last edge
	this->edges[this->edges_size - 1].point1 = this->points[this->points_size - 1];
	this->edges[this->edges_size - 1].point2 = this->points[0];
	this->edges[this->edges_size - 1].CalcolateNormal();
}

sf::Vector2f SatCollisionMesh::GetPosition()
{
	return this->pos;
}

void SatCollisionMesh::SetPosition(sf::Vector2f vec)
{
	this->pos = vec;
}

int SatCollisionMesh::GetEdgesSize()
{
	return this->edges_size;
}

int SatCollisionMesh::GetPointsSize()
{
	return this->points_size;
}

SatEdge* SatCollisionMesh::GetEdges()
{
	return this->edges;
}

sf::Vector2f* SatCollisionMesh::GetPoints()
{
	return this->points;
}


//SAT Algorithm
void SatTask::Do()
{
	sf::Vector2f accAxis;
	float bestMag = 0xffffffff;
	sf::Vector2f bestAxis;
	bool collide = false;

	SatEdge* edges1 = this->collisionMesh1->GetEdges();
	SatEdge* edges2 = this->collisionMesh2->GetEdges();

	sf::Vector2f* points1 = this->collisionMesh1->GetPoints();
	sf::Vector2f* points2 = this->collisionMesh2->GetPoints();

	int coll1_size = this->collisionMesh1->GetEdgesSize();
	int coll2_size = this->collisionMesh2->GetEdgesSize();

	float min1 = 0xffffffff;
	float min2 = 0xffffffff;
	float max1 = -float(0xffffffff);
	float max2 = -float(0xffffffff);

	float temp = 0;

	//calc all collider1 axis
	for (int i = 0; i < coll1_size; i++) {
		accAxis = edges1[i].normalRot90; //usare la normale perpendicolare

		for (int j = 0; j < coll1_size; j++) {
			temp = dotProduct(points1[j], accAxis); // punto priettato sull asse
			if (temp < min1)
				min1 = temp;

			if (temp > max1)
				max1 = temp;
		}

		for (int j = 0; j < coll2_size; j++) {
			temp = dotProduct(points2[j], accAxis); // punto priettato sull asse
			if (temp < min2)
				min2 = temp;

			if (temp > max2)
				max2 = temp;
		}

		//se i due segmenti mono dimesionali si intersecano
		if (max1 >= min2 && max2 >= min1) {

			//calcola se è più corta la soluzione normale o invertita
			float mag = max1 - min2;
			float invMag = max2 - min1;

			if (mag < invMag) {
				if (mag < bestMag) {
					bestMag = mag;
					bestAxis = accAxis;
				}
			}

			else {
				bestMag = invMag;
				bestAxis = accAxis * -1.f;
			}

		}

		//se non intersecano finisci
		else
			return;
	}

	//calc all collider2 axis
	for (int i = 0; i < coll2_size; i++) {
		accAxis = edges2[i].normalRot90; //usare la normale perpendicolare

		for (int j = 0; j < coll1_size; j++) {
			temp = dotProduct(points1[j], accAxis); // punto priettato sull asse
			if (temp < min1)
				min1 = temp;

			if (temp > max1)
				max1 = temp;
		}

		for (int j = 0; j < coll2_size; j++) {
			temp = dotProduct(points2[j], accAxis); // punto priettato sull asse
			if (temp < min2)
				min2 = temp;

			if (temp > max2)
				max2 = temp;
		}

		//se i due segmenti mono dimesionali si intersecano
		if (max1 >= min2 && max2 >= min1) {

			//calcola se è più corta la soluzione normale o invertita
			float mag = max1 - min2;
			float invMag = max2 - min1;

			if (mag < invMag) {
				if (mag < bestMag) {
					bestMag = mag;
					bestAxis = accAxis;
				}
			}

			else {
				bestMag = invMag;
				bestAxis = accAxis * -1.f;
			}

		}

		//se non intersecano finisci
		else
			return;
	}

	this->solution1 = -rotateVector90(bestAxis) * bestMag;

}

void AABBTask::Do()
{
	//axis (1, 0)
	sf::Vector2f axis = sf::Vector2f(1,0);
	float mag = (this->aabb1->GetPosition().x + this->aabb1->GetSize().x) - this->aabb2->GetPosition().x;

	//axis (-1, 0)
	float temp = (this->aabb2->GetPosition().x + this->aabb2->GetSize().x) - this->aabb1->GetPosition().x;
	if (temp < mag) {
		mag = temp;
		axis = sf::Vector2f(-1, 0);
	}
	//axis (0, 1)
	temp = (this->aabb1->GetPosition().y + this->aabb1->GetSize().y) - this->aabb2->GetPosition().y;
	if (temp < mag) {
		mag = temp;
		axis = sf::Vector2f(0, 1);
	}
	//axis (0, -1)
	temp = (this->aabb2->GetPosition().y + this->aabb2->GetSize().y) - this->aabb1->GetPosition().y;
	if (temp < mag) {
		mag = temp;
		axis = sf::Vector2f(0, -1);
	}

	this->solution1 = axis * mag;
}

AABB::AABB()
{
	this->size = sf::Vector2f(0, 0);
	this->position = sf::Vector2f(0, 0);
}

AABB::AABB(float w, float h)
{
	this->size = sf::Vector2f(w, h);
	this->position = sf::Vector2f(0, 0);
}

void AABB::SetPosition(sf::Vector2f pos)
{
	this->position = pos;
}

sf::Vector2f AABB::GetPosition()
{
	return this->position;
}

void AABB::SetSize(sf::Vector2f size)
{
	this->size = size;
}

sf::Vector2f AABB::GetSize()
{
	return this->size;
}

Collider::Collider()
{
	this->isAABB = false;
	this->pos = sf::Vector2f(0, 0);
}

void Collider::GenerateFromAABB(sf::Vector2f size)
{
	this->isAABB = true;
	this->aabb.SetSize(size);
	this->aabb.SetPosition(sf::Vector2f(0, 0));
	this->m_sat_mesh = SatCollisionMesh(std::vector<sf::Vector2f>{sf::Vector2f(0, 0), sf::Vector2f(size.x, 0), size, sf::Vector2f(0, size.y) });
}

void Collider::GenerateFromSATMesh(std::vector<sf::Vector2f> points)
{
	this->isAABB = false;
	sf::Vector2f size(0, 0);
	for (int i = 0; i < points.size(); i++) {
		if (points[i].x > size.x)
			size.x = points[i].x;

		if (points[i].y > size.y)
			size.y = points[i].y;
	}
}

void Collider::UpdatePositions()
{
	this->aabb.SetPosition(this->pos);
	this->m_sat_mesh.SetPosition(this->pos);
}
