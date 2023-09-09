#pragma once
#include "GameEntity.h"
#include "Input/Input.h"
#include "Engine/YorkieEngine.h"
#include "entt/entt.hpp"
#include "Editor/Grid.h"
#include "Logging/Logger.h"

class Camera;

class YorkieAPI Level
{
	friend class LevelEditor;
public: 
	Level(const char* levelName);

	//Function to call each time we want to create a game entity
	template<typename T = GameEntity, typename... Args>
	T* CreateEntity(Args&&... args)
{
		T* gameEntity = new T(std::forward<Args>(args)...);
		if (gameEntity)
		{
			gameEntity->SetupEntity(*this);
			m_GameEntities.push_back(gameEntity);
		}
		else
			Logger::LogError("Game Entity could not be created");

		return gameEntity;
	}

	inline Camera& GetGamera() { return *m_renderCamera; };
	inline entt::registry& GetRegistry() { return registry; };
	inline std::vector<GameEntity*>& GetGameEntities(){ return m_GameEntities; };

private: 
	const char* m_LevelName;

	//All the game entities that are inside the game
	std::vector<GameEntity*> m_GameEntities;

	//Camera used to render the main scene
	Camera* m_renderCamera;
	Grid* grid;

	//Check if the player is in game or browsing through the editor
	bool bIsInGame;

	const glm::vec3 WorldUp;

	//Used for adding components with entt component system
	entt::registry registry;

	void Init();
	void InitGameEntities();
	void UpdateGameEntities(float deltaTime);
};