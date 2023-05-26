#pragma once

#include <list>
#include <glm/glm.hpp>
#include <list>
#include <memory>
#include "BoundingBoxComponent.h"
#include <iostream>
#include "Component.h"
#include <typeindex>

class DrawComponent;
class BoundingBoxComponent;

class GameObject: public std::enable_shared_from_this<GameObject>
{
	std::shared_ptr<DrawComponent> drawComponent;

	std::list<std::shared_ptr<Component>> components;
	std::vector<std::type_index> removeComponentTypes;

public:
	GameObject();
	~GameObject();


	glm::vec3 position;
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);


	void addComponent(std::shared_ptr<Component> component);
	std::list<std::shared_ptr<Component>> getComponents();
	void update(float elapsedTime);
	void draw(const glm::mat4 & = glm::mat4(1.0f));
	std::shared_ptr<GameObject> getSharedPointer();
	glm::vec3 getRotation();
	glm::vec3 getPosition();
	glm::vec3 getScale();


	template<class T>
	std::shared_ptr<T> getComponent()
	{
		for (auto c : components)
		{
			std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(c);
			if (t)
				return t;
		}
		return nullptr;
	}

	template<class T>
	void removeComponent()
	{
		removeComponentTypes.push_back(std::type_index(typeid(T));
	}


};

