#include "YDeleteObjectComponent.h"


//Delete Component when it reaches a specific height
YDeleteObjectComponent::YDeleteObjectComponent(double height, GameManager* manager)
	: deleteableHeight(height), gameManager(manager)
{

}

YDeleteObjectComponent::~YDeleteObjectComponent()
{
}

void YDeleteObjectComponent::update(float elapsedTime)
{
	if (gameObject->position.y < deleteableHeight) {
		gameManager->removeGameObject(gameObject->getSharedPointer());
	}

}
