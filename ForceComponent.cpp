#include "ForceComponent.h"
#include "GameObject.h"
#include <iostream>


ForceComponent::ForceComponent()
{
	forces = glm::vec3(0, 0, 0);
}

ForceComponent::~ForceComponent()
{
}

void ForceComponent::update(float elapsedTime)
{
	gameObject->position.x += elapsedTime * forces.x;
	gameObject->position.y += elapsedTime * forces.y;
	gameObject->position.z += elapsedTime * forces.z;

}

void ForceComponent::addFore(glm::vec3 force)
{
	forces += force;
}

void ForceComponent::multiplyForce(glm::vec3 force)
{
	forces *= force;
}
