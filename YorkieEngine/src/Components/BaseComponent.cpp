#include "Components/BaseComponent.h"

BaseComponent::BaseComponent(BaseComponent* parentComponent, std::vector<BaseComponent*> childComponents, const char* componentName)
{
	this->parentComponent = parentComponent;
	this->childComponents = childComponents;
	this->componentName = componentName;
}
