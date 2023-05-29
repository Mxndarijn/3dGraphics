#pragma once

#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

class FloorTile
{
public:
	FloorTile(glm::vec3 position, float xMultiplier, float zMultiplier);
	~FloorTile();
	void generateNewColor();
	void draw();
	void update(float elapsedTime);
	std::shared_ptr<GameObject> object;
	inline glm::vec4 getCurrentColor() { return currentColor; };
	float floorHeight = 3;
protected:
	glm::vec4 currentColor;
};

