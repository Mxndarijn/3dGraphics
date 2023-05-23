#include "GravityComponent.h"
#include "ForceComponent.h"
#include <iostream>

GravityComponent::GravityComponent()
{
}

GravityComponent::~GravityComponent()
{
	auto forceComponent = gameObject->getComponent<ForceComponent>();
	if (forceComponent != nullptr) {
		forceComponent->multiplyForce(glm::vec3(1, 0, 1));
	}

}

void GravityComponent::update(float elapsedTime)
{
	auto forceComponent = gameObject->getComponent<ForceComponent>();
	if (forceComponent == nullptr) {
		std::cout << "No force component found" << std::endl;
	} else{
		forceComponent->addFore(glm::vec3(0, -9.81, 0) * elapsedTime);
	}
}

void GravityComponent::init()
{
	auto forceComponent = gameObject->getComponent<ForceComponent>();

	if (!forceComponent) {
		gameObject->addComponent(std::make_shared<ForceComponent>());
	}
}
