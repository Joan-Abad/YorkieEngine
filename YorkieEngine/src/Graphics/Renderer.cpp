#include "Graphics/Renderer.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Components/MeshComponent.h"
#include <gtc/matrix_transform.hpp>

glm::mat4 Renderer::projection = glm::mat4(1.0);

void Renderer::ClearColor(glm::vec4 color)
{
	glClearColor(color.x, color.y, color.z, color.w);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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
		//Maybe the projection should come from the camera, as we could render in the screen multiple stuff from multiple cameras. 
		shader.SetUniformMat4("projection", projection);

		auto& Component = gameEntity.GetComponent<MeshComponent>();

		Component.DrawMesh();
	}

	
}

void Renderer::DrawGrid(Camera& renderCamera, Grid& grid)
{
	Shader& shader = grid.GetShader();
	shader.Bind();
	glm::mat4 model(1.0f);
	//Set MVP matrix
	shader.SetUniformMat4("model", model);
	shader.SetUniformMat4("view", renderCamera.GetView());
	//Maybe the projection should come from the camera, as we could render in the screen multiple stuff from multiple cameras. 
	shader.SetUniformMat4("projection", projection);

	grid.DrawGrid();
}

void Renderer::SetProjectionMatrix(Camera& renderCamera, float aspectRatio)
{
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(renderCamera.FOV), aspectRatio, renderCamera.GetNearPlane(), renderCamera.GetFarPlane());
}

