#include "ForceComponent.h"
#include "GameObject.h"
#include <iostream>
#include "CollisionComponent.h"
#include <cmath>


ForceComponent::ForceComponent()
{
	forces = glm::vec3(0, 0, 0);
}

ForceComponent::~ForceComponent()
{
}

void ForceComponent::update(float elapsedTime)
{
	if (forces.x == 0 && forces.y == 0 && forces.z == 0) {
		return;
	}
	auto collisionComponent = gameObject->getComponent<CollisionComponent>();
	auto boundingBoxComponent = gameObject->getComponent<BoundingBoxComponent>();
	if (!collisionComponent || !boundingBoxComponent) {
		gameObject->position += forces * elapsedTime;

		forces.x = 0;
		forces.z = 0;
		return;
	}
	auto pos = gameObject->position;

	auto newPos = pos + forces * elapsedTime;
	auto canMove = collisionComponent->canMoveTo(newPos, boundingBoxComponent);
	if (!canMove) {
		glm::vec3 remainingForces = forces;
		newPos = pos;

		// Loop voor elk van de assen x, y, z
		for (int axis = 0; axis < 3; ++axis) { // 3 for total Axis, X, Y, Z
			float& remainingAxisForce = remainingForces[axis];
			float axisDirection = glm::sign(remainingAxisForce);

			while (std::abs(remainingAxisForce) > 1) { // Zolang er krachten over zijn
				glm::vec3 tempPos = newPos;
				tempPos[axis] += remainingAxisForce * elapsedTime;
				canMove = collisionComponent->canMoveTo(tempPos, boundingBoxComponent);

				if (canMove) {
					newPos = tempPos;
					forces[axis] -= remainingAxisForce;
					break;
				}

				remainingAxisForce -= axisDirection;
			}
		}

		// Reset y-force als het nog steeds groter is dan 1 of kleiner dan -1
		if (std::abs(forces.y) >= 1) {
			forces.y = 0;
		}
	}
	gameObject->position = newPos;
	//Wrijvingskrachts?
	forces.x = 0;
	forces.z = 0;

}

void ForceComponent::addForce(glm::vec3 force)
{
	forces += force;
}

void ForceComponent::multiplyForce(glm::vec3 force)
{
	forces *= force;
}
