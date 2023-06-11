#include "GameObject.h"
#include "DrawComponent.h"
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "BoundingBoxComponent.h"


// Default GameObject class.
GameObject::GameObject()
{
	position = glm::vec3(0, 0, 0);
	forceComponent = std::make_shared<ForceComponent>();
	forceComponent->setGameObject(this);
}


GameObject::~GameObject()
{
}
 
void GameObject::addComponent(std::shared_ptr<Component> component)
{
	component->setGameObject(this);
	component->init();
	components.push_back(component);

	if (drawComponent == nullptr) {
		drawComponent = std::dynamic_pointer_cast<DrawComponent>(component);
	}
}

std::list<std::shared_ptr<Component>> GameObject::getComponents()
{
	return components;
}


void GameObject::draw(const glm::mat4& parentMatrix)
{
	if (!drawComponent)
		return;

	glm::mat4 modelMatrix = parentMatrix;
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, scale);

	tigl::shader->setModelMatrix(modelMatrix);
	drawComponent->draw();
}

glm::vec3 GameObject::getRotation()
{
	return rotation;
}

glm::vec3 GameObject::getPosition()
{
	return position;
}

glm::vec3 GameObject::getScale()
{
	return scale;
}

void GameObject::update(float elapsedTime)
{
	// Remove old components
	if (!removeComponentTypes.empty()) {

		for (const auto& removeType : removeComponentTypes)
		{
			auto it = components.begin();
			while (it != components.end())
			{
				if (std::type_index(typeid(**it)) == removeType)
				{
					it = components.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
		removeComponentTypes.clear();
	}

	for (auto& c : components)
		c->update(elapsedTime);

	forceComponent->update(elapsedTime);
}

std::shared_ptr<GameObject> GameObject::getSharedPointer()
{
	return shared_from_this();
}

void GameObject::removeDrawComponent() {
	drawComponent = nullptr;
}
