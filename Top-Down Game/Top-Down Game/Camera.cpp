#include "Camera.h"



Camera::Camera()
{
	this->followed_entity;
	this->m_trauma = 0;
	this->trauma_reducing = 0.9;
	this->m_camera_smoothness = 0.1;
	this->maxAngleShaking = 2;
	this->maxOffSetShaking = 2;
	this->m_angle = 0;
	this->m_pos = sf::Vector2f(0, 0);
}


Camera::~Camera()
{
}

void Camera::Update(float dt)
{
	//computing camera shake
	ShakingData shake = this->ComputeCameraShake(dt);

	//compute new camera position in base of traked entity
	if (this->m_camera_smoothness == 0)
		this->m_pos = this->followed_entity.lock()->GetPosition();

	if (!this->followed_entity.expired()) {
		std::shared_ptr<Entity> entity = this->followed_entity.lock();

		sf::Vector2f distance = entity->GetPosition() - m_pos;
		sf::Vector2f smoothDistance = distance * (1.f / this->m_camera_smoothness);

		this->m_pos += smoothDistance * dt;
	}

	this->view.setCenter(this->m_pos + this->m_camera_position_offset + (shake.transitional *1.65f));
	this->view.setRotation(this->m_angle + shake.rotational);

	//get direction be

}

void Camera::SetViewToTarget(sf::RenderTarget& target)
{
	
	this->view.setSize(sf::Vector2f(target.getSize()));
	this->view.zoom(2);
	target.setView(this->view);
}

void Camera::AddCameraShake(float force)
{
	this->m_trauma += force;
}

void Camera::SetCameraShake(float force)
{
	this->m_trauma = force;
}

void Camera::SetEntityToFollow(std::weak_ptr<Entity> entity)
{
	this->followed_entity = entity;
}

void Camera::SetTraumaReducing(float tr)
{
	this->trauma_reducing = tr;
}

float Camera::GetTraumaReducing()
{
	return this->trauma_reducing;
}

float Camera::GetMaxAngleShaking()
{
	return maxAngleShaking;
}

void Camera::SetMaxAngleShaking(float maxAngle)
{
	this->maxAngleShaking = maxAngle;
}

float Camera::GetMaxOffSetShaking()
{
	return this->maxOffSetShaking;
}

void Camera::SetMaxOffSetShaking(float offset)
{
	this->maxOffSetShaking = offset;
}

float Camera::GetCameraSmoothness()
{
	return this->m_camera_smoothness;
}

void Camera::SetCameraSmoothness(float smoothness)
{
	this->m_camera_smoothness = smoothness;
}

float Camera::GetCameraAngle()
{
	return this->m_angle;
}

void Camera::SetCameraAngle(float angle)
{
	this->m_angle = angle;
}

sf::Vector2f Camera::GetCameraPositionOffSet()
{
	return this->m_camera_position_offset;
}

void Camera::SetCameraPositionOffSet(sf::Vector2f offset)
{
	this->m_camera_position_offset = offset;
}

float Camera::GetCameraTrauma()
{
	return this->m_trauma;
}

ShakingData Camera::ComputeCameraShake(float dt)
{
	//il vettore che verra aggiunto alla posizione reale;
	sf::Vector2f finalVector(0, 0);
	float finalRotation = 0;

	float shake = pow(this->m_trauma, 2);//get shake value, is pow of 2 for more nice effect, it can be also of 3

	//formula to get shaking effect = MaxOffset * dhake * random_number

	//generate random number from -1 to 1
	float randomNumber = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2)) -1;
	finalRotation = this->maxAngleShaking * shake * randomNumber;

	//generate another random number
	randomNumber = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2)) - 1;
	finalVector.x = this->maxOffSetShaking * shake * randomNumber;

	//generate another random number
	randomNumber = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2)) - 1;
	finalVector.y = this->maxOffSetShaking * shake * randomNumber;

	//reduce camera trauma in time
	if(this->m_trauma > 0)
	this->m_trauma -= dt * this->trauma_reducing;

	if (this->m_trauma < 0)
		this->m_trauma = 0;

	return ShakingData{ finalVector, finalRotation };
}
