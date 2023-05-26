#pragma once
#include "Component.h"
#include "GameObject.h"
#include "GameManager.h"

class YDeleteObjectComponent :
    public Component
{
public:
    YDeleteObjectComponent(double deleteableHeight, GameManager* gameManager);
    ~YDeleteObjectComponent();


    virtual void update(float elapsedTime) override;
protected:
    double deleteableHeight;
    GameManager* gameManager;
};

