#include "CollisionComponent.h"

//Collision component, this component checks that is 
CollisionComponent::CollisionComponent(std::shared_ptr <GameManager> manager)
	: gameManager(manager)
{
}

CollisionComponent::~CollisionComponent()
{
}

bool CollisionComponent::canMoveTo(glm::vec3 position, std::shared_ptr<BoundingBoxComponent> boundingBoxComponent)
{
    auto oldPos = gameObject->position;
    gameObject->position = position;

    auto checkCollision = [&](const std::list<std::shared_ptr<GameObject>>& objects) {
        for (const auto& object : objects) {
            if (object == gameObject->getSharedPointer())
                continue;

            if (boundingBoxComponent->collides(object)) {
                gameObject->position = oldPos;
                return false;
            }
        }
        return true;
    };

    bool canMove = checkCollision(gameManager->getObjects());
    if (!canMove)
        return false;

    canMove = checkCollision(gameManager->getWalls());
    if (!canMove)
        return false;

    gameObject->position = oldPos;
    return true;
}
