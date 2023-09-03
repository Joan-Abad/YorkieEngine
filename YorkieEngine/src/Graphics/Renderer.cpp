#include "Graphics/Renderer.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Components/MeshComponent.h"
#include <gtc/matrix_transform.hpp>
#include "UI/imgui.h"
#include "UI/imgui_impl_opengl3.h"
#include "UI/imgui_impl_glfw.h"
#include "Lighting/BasicLight.h"

glm::mat4 Renderer::projectionMat = glm::mat4(1.0);

void Renderer::Init(GLFWwindow& window)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	InitIm_GUI(window);
}

void Renderer::ClearColor(glm::vec4 color)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(color.x, color.y, color.z, color.w);

	// Clear the screen
}

void Renderer::SetLightColorOnShaders()
{

}

void Renderer::InitIm_GUI(GLFWwindow& window)
{
	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplOpenGL3_Init("#version 410");
	ImGui_ImplGlfw_InitForOpenGL(&window, true);	
}

void Renderer::DrawEntity(Camera& renderCamera, GameEntity& gameEntity)
{
	//TODO: Instead of mesh component, it could be set to some more abstract component, like RenderComponent
	if (gameEntity.HasComponent<MeshComponent>())
	{
		Shader& shader = gameEntity.GetShader();
		shader.Bind();
		if (gameEntity.m_basicLight)
		{
			auto& light = gameEntity.m_basicLight;
			glm::vec3 lightPos = light->GetPosition();

			shader.SetUniform3f("viewPos", renderCamera.GetPosition().x, renderCamera.GetPosition().y, renderCamera.GetPosition().z);

			shader.SetUniform3f("material.specular", 0.5f, 0.5f, 0.5f);
			shader.SetUniform1f("material.shininess", 64.f);

			shader.SetUniform3f("light.position", lightPos.x, lightPos.y, lightPos.z);
			shader.SetUniform3f("light.ambient", 0.1f, 0.1f, 0.1f);
			shader.SetUniform3f("light.diffuse", 0.5f, 0.5f, 0.5f);
			shader.SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
			//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);)
		}

		//Set MVP matrix
		shader.SetUniformMat4("model", gameEntity.GetModel());
		shader.SetUniformMat4("view", renderCamera.GetView());
		//Maybe the projection should come from the camera, as we could render in the screen multiple stuff from multiple cameras. 
		shader.SetUniformMat4("projection", projectionMat);

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
	shader.SetUniformMat4("projection", projectionMat);

	grid.DrawGrid();
}

void Renderer::SetProjectionMatrix(Camera& renderCamera, float aspectRatio)
{
	projectionMat = glm::mat4(1.0f);
	projectionMat = glm::perspective(glm::radians(renderCamera.FOV), aspectRatio, renderCamera.GetNearPlane(), renderCamera.GetFarPlane());
}

