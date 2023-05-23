#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "FloorManager.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "CameraComponent.h"
#include "FloorTile.h"
#include "PlaneComponent.h"
#include "GravityComponent.h"

void addGameObject(std::shared_ptr<GameObject> ob);
void addWall(std::shared_ptr<GameObject> ob);