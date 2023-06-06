#pragma once

#include "FloorManager.h"
#include "GameObject.h"
#include <list>
#include <memory>
#include "Color.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GameStatus.h"
#include <vector>
#include "Texture.h"
#include "ObjModel.h"


class GameManager: std::enable_shared_from_this<GameObject>
{
public:
	GameManager(std::shared_ptr<GameObject> camera);
	~GameManager();

	void update(double elapsedTime);
	void newRound();
	void addGameObject(std::shared_ptr<GameObject> ob);
	void removeGameObject(std::shared_ptr<GameObject> ob);
	void addWall(std::shared_ptr<GameObject> ob);
	void draw();
	void generateNewColor();
	inline std::list<std::shared_ptr<GameObject>> getWalls() {
		return walls;
	}
	inline std::list<std::shared_ptr<GameObject>> getObjects() {
		return objects;
	}

	inline std::vector<std::shared_ptr<ObjModel>> getModels() {
		return models;
	}

	std::shared_ptr<FloorManager> getFloorManager();

protected:
	double timeBetweenColors = 5000;
	double resetTime = 6000;
	double timeLeft = timeBetweenColors * 2;
	glm::vec4 currentColor;
	std::list<std::shared_ptr<GameObject>> objects;
	std::list<std::shared_ptr<GameObject>> walls;
	std::list<std::shared_ptr<GameObject>> removeObjects;
	std::shared_ptr<FloorManager> floorManager;
	GameStatus gameStatus;
	std::vector<std::shared_ptr<Texture>> textures;
	std::vector<std::shared_ptr<ObjModel>> models;
	std::shared_ptr<GameObject> camera;
	std::shared_ptr<GameObject> heart;
	bool hasExtraLife;
};

