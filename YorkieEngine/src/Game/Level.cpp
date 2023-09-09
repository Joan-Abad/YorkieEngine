#include "Game/Level.h"
#include "Camera/Camera.h"

Level::Level(const char* levelName) : WorldUp(glm::vec3(0.0f, 1.0f, 0.0)), grid(nullptr), m_renderCamera(nullptr)
{
	m_LevelName = levelName;
}

void Level::Init()
{
    if (!m_renderCamera)
    {
        //GameCamera
        m_renderCamera = CreateEntity<Camera>();
    }

    grid = new Grid();

    InitGameEntities();
}

void Level::InitGameEntities()
{
    for (const auto& renderObject : m_GameEntities)
    {
        renderObject->Init();
    }
}

void Level::UpdateGameEntities(float deltaTime)
{
    for (const auto& renderObject : m_GameEntities)
    {
        renderObject->Update(deltaTime);
    }
}