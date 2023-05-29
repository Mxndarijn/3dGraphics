#pragma once
#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>

class GameObject;

class ForceComponent :
    public Component
{
public:
    ForceComponent();
    ~ForceComponent();

    virtual void update(float elapsedTime) override;

    void addForce(glm::vec3 force);
    void multiplyForce(glm::vec3 force);
protected:
    glm::vec3 forces;
};

