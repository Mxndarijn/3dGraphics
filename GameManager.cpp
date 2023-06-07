#include "GameManager.h"
#include "FloorTile.h"
#include "BoxComponent.h"
#include <iostream>
#include "ModelComponent.h"
#include "main.h"
#include <fstream>
#include "CollisionComponent.h"

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
   // models.push_back(std::make_shared<ObjModel>("resources/zeppelin/zeppelin.obj")); Too heavy
    models.push_back(std::make_shared<ObjModel>("resources/plane/plane.obj"));
    models.push_back(std::make_shared<ObjModel>("resources/bulbasaur/bulbasaur.obj"));
    models.push_back(std::make_shared<ObjModel>("resources/bat/bat.obj"));

    auto center = floorManager->getCenterPoint();

    heart = std::make_shared<GameObject>();
    // Set heart to wall position, y + 12
    heart->position = glm::vec3(center.x, center.y + 12, center.z - (floorManager->yMultiplier * (zTilesLength - 2)) / 2);
    heart->addComponent(std::make_shared<ModelComponent>(models[1]));
    heart->rotation.x = glm::radians(90.f);
    heart->scale *= 6;

    addGameObject(heart);

    auto zeppelin = std::make_shared<GameObject>();
    zeppelin->position = glm::vec3(center.x, center.y + 7, center.z + (floorManager->yMultiplier * (zTilesLength - 2)) / 2 - 10);
    zeppelin->addComponent(std::make_shared<ModelComponent>(models[2]));
   // zeppelin->rotation.x = glm::radians(90.f);
    zeppelin->scale *= 1;

    addGameObject(zeppelin);

    auto bat = std::make_shared<GameObject>();
    bat->position = glm::vec3(center.x - 20, center.y + 10, center.z - 25);
    bat->addComponent(std::make_shared<ModelComponent>(models[4]));
    bat->rotation.z = glm::radians(-40.f);
    bat->scale *= 3;

    addGameObject(bat);

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
    int teleportBackTreshhold = -50;
    if (camera->position.y < teleportBackTreshhold) {
        // Teleport player back when it reaches -50
        if (hasExtraLife) {
            hasExtraLife = false;
            heart->removeComponent<ModelComponent>();
            heart->removeDrawComponent();
            heart->addComponent(std::make_shared<ModelComponent>(models[0]));
            auto center = getFloorManager()->getCenterPoint();
            camera->position = glm::vec3(center.x, center.y + 12, center.z);
        }
        else {
            auto fileName = "scores.txt";
            std::vector<std::string> scores;
            std::ifstream file(fileName);
            if (file.is_open()) {
                std::string score; 
                while (file >> score) {
                    scores.push_back(score);
                }
                file.close();
            }
            else {
                std::cout << "Could not load scores. Maybe there arent any.";
            }
            scores.push_back(std::to_string(round));



            std::ofstream outputFile(fileName);
            if (outputFile.is_open()) {
                for (const auto& score : scores) {
                    outputFile << score << std::endl;
                }
                outputFile.close();
            }
            else {
                std::cout << "Could not save scores.";
            }
            exit(0);
        }
    }
   
}

void GameManager::newRound() 
{
    round += 1;
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


