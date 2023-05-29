#pragma once
#include "DrawComponent.h"
#include "ObjModel.h"
#include "tigl.h"
#include <memory>

class ModelComponent : public DrawComponent
{
	std::shared_ptr<ObjModel> model;
public:
	ModelComponent(std::shared_ptr<ObjModel> model);
	~ModelComponent();

	virtual void draw() override;
};
