#include "ModelComponent.h"

ModelComponent::ModelComponent(std::shared_ptr<ObjModel> model) : model(model)
{

}

ModelComponent::~ModelComponent()
{

}

void ModelComponent::draw()
{
	model->draw();
}