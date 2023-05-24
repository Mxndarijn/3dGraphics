#include "FloorManager.h"
#include "FloorTile.h"
#include <iostream>
#include "main.h"
#include "BoxComponent.h"
#include "GameManager.h"

FloorManager::FloorManager(int width, int height, GameManager* manager)
	: gameManager(manager)
{
	int xMultiplier = 5;
	int yMultiplier = 5;

	for (int widthIndex = 0; widthIndex < width; widthIndex++) 
	{

		std::vector<std::shared_ptr<FloorTile>> list;
		for (int heightIndex = 0; heightIndex < height; heightIndex++) {
			if (widthIndex == 0 || heightIndex == 0 || widthIndex + 1 == width || heightIndex + 1 == height) {
				auto o = std::make_shared<GameObject>();
				o->position = glm::vec3(widthIndex * xMultiplier, 25 / 2, heightIndex * yMultiplier);
				o->addComponent(std::make_shared<BoxComponent>(glm::vec3(1 * xMultiplier, 25, 1 * yMultiplier), nullptr, 1));
				auto comp = o->getComponent<BoxComponent>();
				comp->setColor(glm::vec4(1.f,1.f,1.f,1.f));
				gameManager->addWall(o);
			}
			else {
				list.push_back(std::make_shared<FloorTile>(glm::vec3(widthIndex * xMultiplier, 0, heightIndex * yMultiplier), xMultiplier, yMultiplier));
			}
		}
		tiles.push_back(list);
	}

	for (auto xTiles : tiles) {
		for (auto tile : xTiles) {
			tile->generateNewColor();
		}
	}


}

FloorManager::~FloorManager()
{

}

void FloorManager::draw()
{
	for (auto xTiles : tiles) {
		for (auto tile : xTiles) {
			tile->draw();
		}
	}
}

glm::vec3 FloorManager::getCenterPoint()
{
	int totalRows = tiles.size();
	int totalCols = tiles.empty() ? 0 : tiles[2].size();

	int centerRow = totalRows / 2;
	int centerCol = totalCols / 2;

	return tiles[centerRow][centerCol]->object->position;
}


