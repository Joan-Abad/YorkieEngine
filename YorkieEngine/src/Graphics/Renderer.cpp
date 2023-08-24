#include "Graphics/Renderer.h"
#include "Game/GameEntity.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

void Renderer::ClearColor(glm::vec4 color)
{
	glClearColor(color.x, color.y, color.z, color.w);

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
