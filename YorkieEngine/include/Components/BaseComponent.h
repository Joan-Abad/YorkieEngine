#pragma once
#include <vector>
#include <string>

class BaseComponent
{
public: 
	BaseComponent();

	std::string componentName;

	//Can have more than one child component
	void AddChildComponent(BaseComponent& childComponent);
	//Can have only 1 parent component
	void AddParentComponent(BaseComponent& parentComponent);
	
	virtual void Start();
	virtual void Update(float deltaTime);
private:
	BaseComponent* parentComponent;
	std::vector<BaseComponent*> childComponents;
};

