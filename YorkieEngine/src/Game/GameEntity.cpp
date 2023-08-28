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

GameEntity::GameEntity(Viewport* viewport) : mViewport(viewport)
{
	entity = viewport->registry.create();
	model = glm::mat4(1.0f);
	position = glm::vec3(0, 0, 0);
	objectName = "NULL NAME";
	shader = nullptr;
	
	RootComponent = &AddComponent<TransformComponent>();
}

GameEntity::GameEntity(const char* objectName)
{
	model = glm::mat4(1.0f);
	position = glm::vec3(0,0,0);
	shader = nullptr;
	mViewport = nullptr;
	
	this->objectName = objectName;
}

GameEntity::GameEntity(const char* objectName, Shader &shader) : GameEntity(objectName)
{
	this->shader = &shader;
}

GameEntity::~GameEntity()
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
	//TODO: Remove from here
	glm::vec3 position = RootComponent->GetMat4()[3];

	// The 'position' vector now contains the x, y, and z coordinates of the object in world space
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;
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

void GameEntity::SetEntityLocation(const glm::vec3& newPosition)
{
	if (RootComponent)
		RootComponent->SetLocation(newPosition.x, newPosition.y, newPosition.z);
}

void GameEntity::SetEntityLocation(float x, float y, float z)
{
	if (RootComponent)
		RootComponent->SetLocation(x,y,z);
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
	model = glm::scale(model, glm::vec3(newScale.x, newScale.y, newScale.z));
}

void GameEntity::SetViewport(Viewport* viewport)
{
	this->mViewport = viewport;
}

glm::vec3 &GameEntity::GetEntityLocation() 
{
	return RootComponent->GetLocation();
}
