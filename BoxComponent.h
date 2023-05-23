#pragma once
#include "DrawComponent.h"
#include <glm/gtc/matrix_transform.hpp>
class Texture;

class BoxComponent :
    public DrawComponent
{
public:
    BoxComponent(glm::vec3 transform, Texture* texture = nullptr, int textureMultiValue = 0);
    ~BoxComponent();

    void drawBoxTexture();
    void drawBoxColor();

    void draw() override;

    inline void setColor(glm::vec4 color) { this->color = color; }

protected:
    int textureMulti;
    glm::vec3 transform;
    Texture* texture;
    glm::vec4 color;

};

