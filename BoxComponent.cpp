#include "BoxComponent.h"
#include "tigl.h"
#include "GameObject.h"
#include "Texture.h"
#include <iostream>

using tigl::Vertex;

BoxComponent::BoxComponent(glm::vec3 transform, Texture* texture, int textureMultiValue)
    : transform(transform), texture(texture), textureMulti(textureMultiValue)
{
    color = glm::vec4(0, 255, 255, 1);
}

BoxComponent::~BoxComponent()
{
}

void BoxComponent::drawBoxTexture()
{

    tigl::shader->enableTexture(true);
    tigl::begin(GL_QUADS);

    // achterkant z
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(0, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(0, 1 * textureMulti)));
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMulti, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMulti, 1 * textureMulti)));

    // voorkant z
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(0, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(0, 1 * textureMulti)));
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(1 * textureMulti, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(1 * textureMulti, 1 * textureMulti)));

    // onderkant y
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(0, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMulti, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(0, 1 * textureMulti)));
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(1 * textureMulti, 1 * textureMulti)));

    // bovenkant y
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(0, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMulti, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(0, 1 * textureMulti)));
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(1 * textureMulti, 1 * textureMulti)));

    // linkerkant x
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(0, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMulti, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(0, 1 * textureMulti)));
    tigl::addVertex(Vertex::PT(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(1 * textureMulti, 1 * textureMulti)));

    // rechterkant x
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), glm::vec2(0, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), glm::vec2(1 * textureMulti, 0)));
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), glm::vec2(0, 1 * textureMulti)));
    tigl::addVertex(Vertex::PT(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), glm::vec2(1 * textureMulti, 1 * textureMulti)));

    tigl::end();
    tigl::shader->enableTexture(false);
}

void BoxComponent::drawBoxColor()
{
    tigl::shader->enableColor(true);
    tigl::begin(GL_QUADS);

    // achterkant z
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), color));

    // voorkant z
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), color));

    // onderkant y
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), color));

    // bovenkant y
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), color));

    // linkerkant x
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, -transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, -transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, transform.y / 2, transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(-transform.x / 2, -transform.y / 2, transform.z / 2), color));

    // rechterkant x
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, -transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, -transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, transform.y / 2, transform.z / 2), color));
    tigl::addVertex(Vertex::PC(glm::vec3(transform.x / 2, -transform.y / 2, transform.z / 2), color));

    tigl::end();
    tigl::shader->enableColor(false);
}

void BoxComponent::draw()
{
    if (texture) {
        texture->bind();
        drawBoxTexture();
        texture->unbind();
    }
    else {
        drawBoxColor();
    }
}
