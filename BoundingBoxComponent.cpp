#include "BoundingBoxComponent.h"
#include "GameObject.h"
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>


BoundingBoxComponent::BoundingBoxComponent(glm::vec3 min, glm::vec3 max)
    : min(min), max(max)
{
    lengths = max - min;
}

BoundingBoxComponent::~BoundingBoxComponent()
{
}

bool BoundingBoxComponent::collides(std::shared_ptr<GameObject> other)
{
    auto boundingBoxComponent = other->getComponent<BoundingBoxComponent>();
    if (!boundingBoxComponent)
        return false;

    auto cubeCorner1 = gameObject->position + min;
    auto cubeCorner2 = gameObject->position + max;

    auto corners = getCubeCorners(cubeCorner1, cubeCorner2);

    auto checkingCubeCorner1 = other->position + boundingBoxComponent->min;
    auto checkingCubeCorner2 = other->position + boundingBoxComponent->max;

    for (auto corner : corners) {
        if (isPointInCube(corner, checkingCubeCorner1, checkingCubeCorner2)) { 
            return true;
        }
    }
    return false;
}

std::array<glm::vec3, 4> BoundingBoxComponent::getCubeCorners(glm::vec3 corner1, glm::vec3 corner2)
{
    std::array<glm::vec3, 4> corners;

    glm::vec3 minBounds = glm::min(corner1, corner2);
    glm::vec3 maxBounds = glm::max(corner1, corner2);

    corners[0] = glm::vec3(minBounds.x, minBounds.y, minBounds.z);
    corners[1] = glm::vec3(minBounds.x, maxBounds.y, maxBounds.z);
    corners[2] = glm::vec3(maxBounds.x, maxBounds.y, minBounds.z);
    corners[3] = glm::vec3(maxBounds.x, minBounds.y, maxBounds.z);

    return corners;
}

bool BoundingBoxComponent::isPointInCube(glm::vec3 point, glm::vec3 corner1, glm::vec3 corner2)
{
    glm::vec3 minBounds = glm::min(corner1, corner2);
    glm::vec3 maxBounds = glm::max(corner1, corner2);

    return glm::all(glm::greaterThanEqual(point, minBounds)) &&
        glm::all(glm::lessThanEqual(point, maxBounds));
}