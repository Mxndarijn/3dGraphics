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
	void update(float deltaTime);
	void removeIncorrectFloorTiles(glm::vec4 color);
	glm::vec3 getCenterPoint();

	void generateNewColors();
protected:
	GameManager* gameManager;
	int xMultiplier = 5;
	int yMultiplier = 5;

};

