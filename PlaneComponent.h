#pragma once
#include "DrawComponent.h"
#include <glm/gtc/matrix_transform.hpp>
class Texture;

class PlaneComponent :
    public DrawComponent
{
public:
    PlaneComponent(float width, float height,Texture* texture, int textureMulti);
    ~PlaneComponent();

    void drawPlaneTexture();
    void drawPlaneColor();

    void draw() override;

    inline void setColor(glm::vec4 color) { this->color = color; }
protected:
    int textureMulti;
    float width;
    float height;
    Texture* texture;
    glm::vec4 color;


};

