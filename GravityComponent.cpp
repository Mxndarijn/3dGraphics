#include "GravityComponent.h"
#include "ForceComponent.h"
#include <iostream>

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
		forceComponent->addForce(glm::vec3(0, -3, 0)); // 9.81
	}
}

void GravityComponent::init()
{
}
