#include "FloorTile.h"
#include "PlaneComponent.h"
#include <iostream>
#include "Color.h"
#include "BoxComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GravityComponent.h"

FloorTile::FloorTile(glm::vec3 position, float xMultiplier, float zMultiplier)
{
	srand(time(NULL));
	object = std::make_shared<GameObject>();
	position -= glm::vec3(0, floorHeight / 2, 0);
	object->position = position;
	glm::vec3 size = glm::vec3(1 * xMultiplier, floorHeight, 1 * zMultiplier);
	//std::cout << "Created: " << object->position.x << " " << object->position.y << " " << object->position.z << " Size: " << size.x << " " << size.y << " " << size.z << std::endl;
	object->addComponent(std::make_shared<BoxComponent>(size, nullptr, 1));
	object->addComponent(std::make_shared<BoundingBoxComponent>(size * -0.5f, size * 0.5f));

	
	//object->addComponent(std::make_shared<GravityComponent>());
	//object->addComponent(std::make_shared<PlaneComponent>(1 * xMultiplier,1 * zMultiplier,nullptr, 1));
	
}

FloorTile::~FloorTile()
{

}

void FloorTile::generateNewColor()
{
	auto o = object->getComponent<BoxComponent>();
	int random = rand() % color::colors.size();
	currentColor = color::colors[random];
	o->setColor(currentColor);

}

void FloorTile::draw()
{

	object->draw();
}

void FloorTile::update(float elapsedTime)
{
	object->update(elapsedTime);
}
