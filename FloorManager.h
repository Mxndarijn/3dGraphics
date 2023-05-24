#pragma once

#include <vector>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>

class FloorTile;
class GameManager;

class FloorManager
{

public:
	std::vector<std::vector<std::shared_ptr<FloorTile>>> tiles;

	FloorManager(int width, int heigt, GameManager* manager);
	~FloorManager();
	void draw();
	glm::vec3 getCenterPoint();
protected:
	GameManager* gameManager;

};

