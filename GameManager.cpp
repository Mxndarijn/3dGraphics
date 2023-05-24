#include "GameManager.h"
#include "FloorTile.h"
#include "BoxComponent.h"
#include <iostream>

GameManager::GameManager()
{
	floorManager = std::make_shared<FloorManager>(15, 15, this);
    srand(time(NULL));
	newRound();
}

GameManager::~GameManager()
{

}

void GameManager::update(double elapsedTime)
{
	timeLeft -= elapsedTime * 1000;
	if (timeLeft < 0) {
        std::cout << "New round started" << std::endl;
		timeLeft = timeBetweenColors;
		newRound();
	}
    for (auto xTiles : floorManager->tiles) {
        for (auto tile : xTiles) {
            tile->update(elapsedTime);
        }
    }
    for (auto object : objects) {
        object->update(elapsedTime);
    }

    for (auto object : walls) {
        object->update(elapsedTime);
    }

}

void GameManager::newRound() 
{
    generateNewColor();

    for (auto ob : walls) {
        auto drawComp = ob->getComponent<BoxComponent>();
        drawComp->setColor(currentColor);
        ob->draw();
    }


}

std::shared_ptr<FloorManager> GameManager::getFloorManager()
{
    return floorManager;
}

void GameManager::addGameObject(std::shared_ptr<GameObject> ob) {
    objects.push_back(ob);
}


void GameManager::addWall(std::shared_ptr<GameObject> ob) {
    walls.push_back(ob);
}

void GameManager::draw()
{
    floorManager->draw();
    for (auto ob : objects) {
        ob->draw();
    }

    for (auto ob : walls) {
        ob->draw();
    }
}

void GameManager::generateNewColor()
{
    int random = rand() % color::colors.size();
    glm::vec4 newColor = color::colors[random];
    while (newColor == currentColor) {
        random = rand() % color::colors.size();
        newColor = color::colors[random];
    }
    currentColor = color::colors[random];

}


