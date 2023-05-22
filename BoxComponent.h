#pragma once
#include "DrawComponent.h"
#include <glm/gtc/matrix_transform.hpp>
class Texture;

class BoxComponent :
    public DrawComponent
{
public:
    BoxComponent(float xLength, float yLength, float zLength);
    ~BoxComponent();

    void drawPlaneTexture();
    void drawPlaneColor();

    void draw() override;

    inline void setColor(glm::vec4 color) { this->color = color; }

protected:
    float xLength;
    float yLength;
    float zLength;
    Texture* texture;
    glm::vec4 color;

};

