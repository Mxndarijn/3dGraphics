#include "PlayerComponent.h"
#include "GameObject.h"
#include <GLFW/glfw3.h>

extern GLFWwindow* window;


PlayerComponent::PlayerComponent()
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::move(float angle, float fac, float elapsedTime)
{
	auto forceComponent = gameObject->getForceComponent();
	forceComponent->addForce(glm::vec3(
		(float)cos(gameObject->rotation.y + glm::radians(angle)) * fac * speed, 
		0,
		(float)sin(gameObject->rotation.y + glm::radians(angle)) * fac * speed));
}

void PlayerComponent::update(float elapsedTime)
{	
	// First value is degrees, second one speed.
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move(-90, 0.05f, elapsedTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(90, 0.05f, elapsedTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(180, 0.05f, elapsedTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(0, 0.05f, elapsedTime);

}