#include "FloorManager.h"
#include "FloorTile.h"
#include <iostream>
#include "main.h"
#include "BoxComponent.h"
#include "GameManager.h"
#include "YDeleteObjectComponent.h"
#include "MoveToComponent.h"
#include <thread>

FloorManager::FloorManager(int width, int height, GameManager* manager)
	: gameManager(manager)
{

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

void FloorManager::update(float deltaTime)
{
	for (auto xTiles : tiles) {
		for (auto tile : xTiles) {
			tile->update(deltaTime);
		}
	}
}



void FloorManager::removeIncorrectFloorTiles(glm::vec4 color)
{
	std::vector<std::vector<std::shared_ptr<FloorTile>>> newTiles;
	for (auto xTiles : tiles) {
		std::vector<std::shared_ptr<FloorTile>> list;
		for (auto tile : xTiles) {
			if (tile->getCurrentColor() != color) {
				tile->object->addComponent(std::make_shared<GravityComponent>());
				tile->object->addComponent(std::make_shared<YDeleteObjectComponent>(-20, gameManager));

				auto pos = glm::vec3(tile->object->position.x, 50, tile->object->position.z);
				auto ob = std::make_shared<FloorTile>(pos, xMultiplier, yMultiplier);
				std::thread t([ob](){
					std::this_thread::sleep_for(std::chrono::seconds(3));
					ob->object->addComponent(std::make_shared<MoveToComponent>(glm::vec3(ob->object->position.x, 0, ob->object->position.z)));
				});
				t.detach();

				
				list.push_back(ob);
				gameManager->addGameObject(tile->object);
			}
			else {
				list.push_back(tile);
			}
		}
		newTiles.push_back(list);
	}
	tiles = newTiles;
}

glm::vec3 FloorManager::getCenterPoint()
{
	int totalRows = tiles.size();
	int totalCols = tiles.empty() ? 0 : tiles[2].size();

	int centerRow = totalRows / 2;
	int centerCol = totalCols / 2;

	return tiles[centerRow][centerCol]->object->position;
}

void FloorManager::generateNewColors()
{
	for (auto xTiles : tiles) {
		for (auto tile : xTiles) {
			tile->generateNewColor();
		}
	}
}


