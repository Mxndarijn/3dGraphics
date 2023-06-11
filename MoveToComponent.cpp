#include "MoveToComponent.h"
#include <iostream>


//Moveto component. Does not work with forces.
MoveToComponent::MoveToComponent(glm::vec3 target) :
	target(target)
{
}

MoveToComponent::~MoveToComponent()
{
}

void MoveToComponent::update(float elapsedTime)
{
	auto minDistanceTraveled = 0.025f;

	auto newPos = (1 - speed) * gameObject->position + speed * target;
	auto distanceTraveled = glm::length(newPos - gameObject->position);
	if (distanceTraveled < minDistanceTraveled && glm::length(gameObject->position - target) >= minDistanceTraveled) {
		glm::vec3 direction = glm::normalize(target - gameObject->position);
		newPos = gameObject->position + direction * minDistanceTraveled;
	}
	gameObject->position = newPos;
}
