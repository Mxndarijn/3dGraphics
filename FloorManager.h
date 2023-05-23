#pragma once

#include <vector>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>

class FloorTile;

class FloorManager
{

public:
	std::vector<std::vector<std::shared_ptr<FloorTile>>> tiles;

	FloorManager(int width, int heigt);
	~FloorManager();
	void draw();
	glm::vec3 getCenterPoint();



};

