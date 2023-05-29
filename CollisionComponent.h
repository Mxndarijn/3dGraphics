#pragma once
#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>
#include "BoundingBoxComponent.h"
#include <memory>
#include "GameManager.h"

class CollisionComponent :
    public Component
{
    std::shared_ptr <GameManager> gameManager;
public:
    CollisionComponent(std::shared_ptr <GameManager> manager);
    ~CollisionComponent();

    virtual void update(float elapsedTime) override {};

    bool canMoveTo(glm::vec3 position, std::shared_ptr<BoundingBoxComponent> boundingBoxComponent);
};

