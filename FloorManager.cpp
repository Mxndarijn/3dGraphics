#include "FloorManager.h"
#include "FloorTile.h"
#include <iostream>

FloorManager::FloorManager(int width, int height)
{
	int xMultiplier = 5;
	int yMultiplier = 5;

	for (int widthIndex = 0; widthIndex < width; widthIndex++) 
	{

		std::vector<std::shared_ptr<FloorTile>> list;
		for (int heightIndex = 0; heightIndex < height; heightIndex++) {
			list.push_back(std::make_shared<FloorTile>(glm::vec3(widthIndex * xMultiplier, 0, heightIndex * yMultiplier), xMultiplier, yMultiplier));
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


