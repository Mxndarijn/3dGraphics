#include "GravityComponent.h"
#include "ForceComponent.h"
#include <iostream>

//GravityComponents that adds a force to below.
GravityComponent::GravityComponent()
{
}

GravityComponent::~GravityComponent()
{
}

void GravityComponent::update(float elapsedTime)
{
	auto forceComponent = gameObject->getForceComponent();
	if (forceComponent == nullptr) {
		std::cout << "No force component found" << std::endl;
	} else{
		int forcePower = -3;
		forceComponent->addForce(glm::vec3(0, forcePower, 0)); // Voeg een kracht van -3 toe op een object.
	}
}

void GravityComponent::init()
{
}
