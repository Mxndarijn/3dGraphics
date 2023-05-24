#include "FloorTile.h"
#include "PlaneComponent.h"
#include <iostream>
#include "Color.h"
#include "BoxComponent.h"
#include "GravityComponent.h"

FloorTile::FloorTile(glm::vec3 position, int xMultiplier, int zMultiplier)
{
	srand(time(NULL));
	object = std::make_shared<GameObject>();
	position -= glm::vec3(0, 3 / 2, 0);
	object->position = position;
	object->addComponent(std::make_shared<BoxComponent>(glm::vec3(1 * xMultiplier,3, 1 * zMultiplier), nullptr, 1));
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
	glm::vec4 sel_elem = color::colors[random];
	o->setColor(sel_elem);

}

void FloorTile::draw()
{

	object->draw();
}

void FloorTile::update(float elapsedTime)
{
	object->update(elapsedTime);
}
