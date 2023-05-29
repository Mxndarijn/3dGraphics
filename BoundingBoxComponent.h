#pragma once

#include <glm/glm.hpp>
#include "Component.h"
#include <memory>
#include "GameObject.h"

class BoundingBoxComponent : public Component
{
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 lengths;
public:
	virtual void update(float elapsedTime) override {};
	BoundingBoxComponent(glm::vec3 min, glm::vec3 max);
	~BoundingBoxComponent();
	bool collides(std::shared_ptr<GameObject> other);
	std::array<glm::vec3, 4> getCubeCorners(glm::vec3 corner1, glm::vec3 corner2);
	bool isPointInCube(glm::vec3 point, glm::vec3 corner1, glm::vec3 corner2);
};

