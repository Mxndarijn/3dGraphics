#include "MoveToComponent.h"
#include <iostream>

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

	//not needed.
	//float angle = atan2(gameObject->position.z - target.z, gameObject->position.x - target.x);

	//gameObject->rotation.y = 0.05f * angle + 0.95f * gameObject->rotation.y;

	auto pos = gameObject->position;

	if (glm::length(pos - target) < 0.01f) {
		gameObject->position = target;
		gameObject->removeComponent<MoveToComponent>();
	}
}
