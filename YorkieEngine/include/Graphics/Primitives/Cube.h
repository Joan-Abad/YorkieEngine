#pragma once
#include "Engine/YorkieEngine.h"
#include "Game/GameEntity.h"
#include <vector>

class YorkieAPI Cube : public GameEntity
{
public: 
	Cube();

	virtual void OnConstruct();
};

