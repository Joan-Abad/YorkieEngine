#include "Graphics/Renderer.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Components/MeshComponent.h"

void Renderer::ClearColor(glm::vec4 color)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(color.x, color.y, color.z, color.w);

	// Clear the screen
}

void Renderer::DrawEntity(Camera& renderCamera, GameEntity& gameEntity)
{
	//TODO: Instead of mesh component, it could be set to some more abstract component, like RenderComponent
	if (gameEntity.HasComponent<MeshComponent>())
	{
		Shader& shader = gameEntity.GetShader();
		shader.Bind();

		//Set MVP matrix
		shader.SetUniformMat4("model", gameEntity.GetModel());
		shader.SetUniformMat4("view", renderCamera.GetView());
		shader.SetUniformMat4("projection", renderCamera.GetProjection());

		auto& Component = gameEntity.GetComponent<MeshComponent>();

		Component.DrawMesh();
	}

	
}

