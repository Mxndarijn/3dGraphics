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
        if (gameStatus == GameStatus::RESETTING) {
            gameStatus = GameStatus::RUNNING;
            timeLeft = timeBetweenColors;
        }
        else {
            floorManager->removeIncorrectFloorTiles(currentColor);
            newRound();
        }
	}
    floorManager->update(elapsedTime);
    for (auto object : objects) {
        object->update(elapsedTime);
    }

    for (auto object : walls) {
        object->update(elapsedTime);
    }

    for (auto object : removeObjects) {
        objects.remove(object);
        object.reset();
    }

    if (removeObjects.empty()) {
        removeObjects.clear();
    }
   
}

void GameManager::newRound() 
{

    generateNewColor();

    for (auto ob : walls) {
        auto drawComp = ob->getComponent<BoxComponent>();
        drawComp->setColor(currentColor);
    }
    gameStatus = GameStatus::RESETTING;
    timeLeft = resetTime;



}

std::shared_ptr<FloorManager> GameManager::getFloorManager()
{
    return floorManager;
}

void GameManager::addGameObject(std::shared_ptr<GameObject> ob) {
    objects.push_back(ob);
}

void GameManager::removeGameObject(std::shared_ptr<GameObject> ob)
{
    removeObjects.push_back(ob);
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

    floorManager->generateNewColors();

}


