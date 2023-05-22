#include "FloorTile.h"
#include "PlaneComponent.h"
#include <iostream>
#include "Color.h"

FloorTile::FloorTile(glm::vec3 position, int xMultiplier, int zMultiplier)
{
	object = std::make_shared<GameObject>();
	object->position = position;
	object->addComponent(std::make_shared<PlaneComponent>(1 * xMultiplier,1 * zMultiplier,nullptr, 1));
}

FloorTile::~FloorTile()
{

}

void FloorTile::generateNewColor()
{
	auto o = object->getComponent<PlaneComponent>();
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
