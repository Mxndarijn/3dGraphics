#pragma once

#include "FloorManager.h"
#include "GameObject.h"
#include <list>
#include <memory>
#include "Color.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GameStatus.h"


class GameManager
{
public:
	GameManager();
	~GameManager();

	void update(double elapsedTime);
	void newRound();
	void addGameObject(std::shared_ptr<GameObject> ob);
	void removeGameObject(std::shared_ptr<GameObject> ob);
	void addWall(std::shared_ptr<GameObject> ob);
	void draw();
	void generateNewColor();

	std::shared_ptr<FloorManager> getFloorManager();

protected:
	double timeBetweenColors = 5000;
	double resetTime = 5000;
	double timeLeft = timeBetweenColors * 2;
	glm::vec4 currentColor;
	std::list<std::shared_ptr<GameObject>> objects;
	std::list<std::shared_ptr<GameObject>> walls;
	std::list<std::shared_ptr<GameObject>> removeObjects;
	std::shared_ptr<FloorManager> floorManager;
	GameStatus gameStatus;
};

