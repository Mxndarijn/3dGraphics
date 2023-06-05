#include "PlaneComponent.h"
#include "tigl.h"
#include "GameObject.h"
#include "Texture.h"
#include <iostream>

using tigl::Vertex;

PlaneComponent::PlaneComponent(float width, float height, Texture* texture, int textureMultiValue)
	: textureMulti(textureMultiValue), width(width), height(height), texture(texture)
{
	color = glm::vec4(0, 255, 255, 1); // Set color to blue
}

PlaneComponent::~PlaneComponent()
{
}

void PlaneComponent::drawPlaneTexture()
{
	tigl::shader->enableTexture(true);
	tigl::begin(GL_QUADS);
	// Calulate corners
	tigl::addVertex(Vertex::PT(glm::vec3(-width / 2, 0 / 2, -height / 2), glm::vec2(0, 0)));
	tigl::addVertex(Vertex::PT(glm::vec3(width / 2, 0 / 2, -height / 2), glm::vec2( textureMulti, 0)));
	tigl::addVertex(Vertex::PT(glm::vec3(width / 2, 0 / 2, height / 2), glm::vec2(0,  textureMulti)));
	tigl::addVertex(Vertex::PT(glm::vec3(-width / 2, 0 / 2, height / 2), glm::vec2( textureMulti,  textureMulti)));

	tigl::end();
	tigl::shader->enableTexture(false);
}

void PlaneComponent::drawPlaneColor()
{
	tigl::shader->enableColor(true);
	tigl::begin(GL_QUADS);

	// Calculate Corners
	tigl::addVertex(Vertex::PC(glm::vec3(-width / 2, 0 / 2, -height / 2), color));
	tigl::addVertex(Vertex::PC(glm::vec3(width / 2, 0 / 2, -height / 2), color));
	tigl::addVertex(Vertex::PC(glm::vec3(width / 2, 0 / 2, height / 2), color));
	tigl::addVertex(Vertex::PC(glm::vec3(-width / 2, 0 / 2, height / 2), color));

	tigl::end();
}

void PlaneComponent::draw()
{
	if (texture) {
		texture->bind();
		drawPlaneTexture();
		texture->unbind();
	}
	else
		drawPlaneColor();
}
