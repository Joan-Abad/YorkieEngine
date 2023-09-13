#include "Game/GameEntity.h"
#include <sstream>
#include <vector>
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Window/Window.h"
#include "Modules/ShaderModule.h"
#include <iostream>
#include "Window/Viewport.h"
#include "entt/entity/registry.hpp"

unsigned int GameEntity::entityID = 1;

GameEntity::GameEntity() : shader(nullptr), m_Level(nullptr), RootComponent(nullptr), m_PointLight(nullptr)
{
	entityName = "GameEntity_ " + std::to_string(entityID);
	entityID++;
}

GameEntity::~GameEntity()
{
}


void GameEntity::OnConstruct()
{

}

void GameEntity::Init()
{
	if (!shader)
		shader = ShaderModule::GetShaderModule()->GetDefaultShader();
}



void GameEntity::Update(float deltaTime)
{
	for (auto& component : components)
	{
		component->Update(deltaTime);
	}
}

void GameEntity::PostUpdate()
{	

}

void GameEntity::AttachShader(Shader* shader)
{
    this->shader = shader;
}

void GameEntity::AddOffstet(float x, float y, float z)
{
	if (RootComponent)
		RootComponent->AddOffstet(x, y, z);
}

void GameEntity::AddOffstet(const glm::vec3& newPosition)
{
	if (RootComponent)
		RootComponent->AddOffstet(newPosition);
}

void GameEntity::AddScale(float x, float y, float z)
{
	if (RootComponent)
		RootComponent->AddScale(x,y,z);
}

void GameEntity::AddScale(glm::vec3& newScale)
{
	if (RootComponent)
		RootComponent->AddScale(newScale);
}

void GameEntity::AddRotation(float Roll, float Pitch, float Yaw)
{
	if (RootComponent)
		RootComponent->AddRotation(Roll, Pitch, Yaw);
}

void GameEntity::SetPosition(const glm::vec3& newPosition)
{
	if (RootComponent)
	{
		RootComponent->SetPosition(newPosition.x, newPosition.y, newPosition.z);
	}
}

void GameEntity::SetPosition(float x, float y, float z)
{
	if (RootComponent)
		RootComponent->SetPosition(x,y,z);
}

void GameEntity::SetRotation(float Roll, float Pitch, float Yaw)
{
	if (RootComponent)
		RootComponent->SetRotation(Roll, Pitch, Yaw);
}

void GameEntity::SetScale(float x, float y, float z)
{
	if (RootComponent)
		RootComponent->SetScale(x,y,z);
}

void GameEntity::SetScale(glm::vec3& newScale)
{
	if (RootComponent)
		RootComponent->SetScale(newScale.x, newScale.y, newScale.z);
}

void GameEntity::SetViewport(Level& level)
{
	m_Level = &level;
	entity = m_Level->GetRegistry().create();
}

void GameEntity::SetupEntity(Level& level)
{
	m_Level = &level;
	entity = m_Level->GetRegistry().create();
	RootComponent = &AddComponent<TransformComponent>();
	OnConstruct();
}
