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
	float minSpeed = 0.1f; // Adjust the minimum speed as needed
	float clampedSpeed = std::max(speed, minSpeed);

	glm::vec3 direction = glm::normalize(target - gameObject->position);
	float distance = glm::distance(gameObject->position, target);
	float moveDistance = std::min(distance, clampedSpeed * elapsedTime);

	gameObject->position += direction * moveDistance;

	float angle = atan2(gameObject->position.z - target.z, gameObject->position.x - target.x);

	gameObject->rotation.y = 0.05f * angle + 0.95f * gameObject->rotation.y;

	auto pos = gameObject->position;
	float distanceToTarget = glm::length(pos - target);
	float distanceThreshold = 0.05f; // Adjust this threshold as needed

	if (distance < distanceThreshold) {
		gameObject->position = target;
		std::cout << "Removing MoveTo" << std::endl;
		gameObject->removeComponent<MoveToComponent>();
	}
}
