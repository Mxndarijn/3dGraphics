#include "GameManager.h"
#include "FloorTile.h"
#include "BoxComponent.h"
#include <iostream>
#include "ModelComponent.h"
#include "main.h"

GameManager::GameManager(std::shared_ptr<GameObject> camera)
    : camera(camera)
{
    int xTilesLength = 15;
    int zTilesLength = 15;
    hasExtraLife = true;

	floorManager = std::make_shared<FloorManager>(xTilesLength, zTilesLength, this);
    srand(time(NULL));
	newRound();

    models.push_back(std::make_shared<ObjModel>("resources/broken_heart/gebrokenhart.obj"));
    models.push_back(std::make_shared<ObjModel>("resources/heart/heelhart.obj"));

    auto center = floorManager->getCenterPoint();

    heart = std::make_shared<GameObject>();
    heart->position = glm::vec3(center.x, center.y + 12, center.z - (floorManager->yMultiplier * (zTilesLength - 2)) / 2);
    heart->addComponent(std::make_shared<ModelComponent>(models[1]));
    heart->rotation.x = glm::radians(90.f);
    heart->scale *= 6;
    addGameObject(heart);
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
    if (hasExtraLife) {
        int teleportBackTreshhold = -50;
        if (camera->position.y < teleportBackTreshhold) {
            hasExtraLife = false;
            heart->removeComponent<ModelComponent>();
            heart->removeDrawComponent();
            heart->addComponent(std::make_shared<ModelComponent>(models[0]));
            auto center = getFloorManager()->getCenterPoint();
            camera->position = glm::vec3(center.x, center.y + 12, center.z);
        }
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


