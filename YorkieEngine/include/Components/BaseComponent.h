#pragma once
#include <vector>

class BaseComponent
{
public: 
	BaseComponent(BaseComponent* parentComponent, std::vector<BaseComponent*> childComponents, const char* componentName);
	BaseComponent* parentComponent;
	std::vector<BaseComponent*> childComponents;
	const char* componentName;
};

