#pragma once
#include "Component.h"
#include "GameObject.h"
class GravityComponent :
    public Component
{
public:
    GravityComponent();
    ~GravityComponent();

    virtual void update(float elapsedTime) override;
    virtual void init() override;
    
};

