#include "Components/BaseComponent.h"

BaseComponent::BaseComponent()
{
	this->componentName = "Base Component";
}

void BaseComponent::AddParentComponent(BaseComponent& parentComponent)
{
	this->parentComponent = &parentComponent;
}

void BaseComponent::Start()
{
}

void BaseComponent::Update(float deltaTime)
{
}

void BaseComponent::AddChildComponent(BaseComponent& childComponent)
{
	childComponents.push_back(&childComponent);
}
