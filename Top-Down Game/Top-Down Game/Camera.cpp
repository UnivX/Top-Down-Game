#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Update(float dt)
{
	//computing camera shake
}

void Camera::AddCameraShake(float force)
{
	this->m_trauma += force;
}

ShakingData Camera::ComputeCameraShake(float dt)
{
	//il vettore che verra aggiunto alla posizione reale;
	sf::Vector2f finalVector(0, 0);
	float finalRotation = 0;

	

	//reduce camera trauma in time
	this->m_trauma = dt * this->trauma_reducing;

	return ShakingData{ finalVector, finalRotation };
}
