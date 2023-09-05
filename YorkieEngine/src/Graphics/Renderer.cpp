#include "Graphics/Renderer.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Components/MeshComponent.h"
#include <gtc/matrix_transform.hpp>
#include "UI/imgui.h"
#include "UI/imgui_impl_opengl3.h"
#include "UI/imgui_impl_glfw.h"
#include "Lighting/BasicLight.h"
#include "Graphics/Materials/Material.h"
#include "Graphics/Texture/Texture.h"
#include "Game/Lights/PointLight.h"

glm::mat4 Renderer::projectionMat = glm::mat4(1.0);
Grid* Renderer::m_sceneGrid = nullptr;
DirectionalLight* Renderer::m_DirectionalLight = nullptr;

void Renderer::Init(GLFWwindow& window)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	InitIm_GUI(window);

	//TODO: REMOVE FROM HERE TO LEVEL
	m_sceneGrid = new Grid();
	m_DirectionalLight = new DirectionalLight();
	m_DirectionalLight->m_specularColor = glm::vec3(1.0f, 1.0f, 0.1f);
	m_DirectionalLight->m_ambientColor = glm::vec3(0.1f, 0.1f, 0.1f);
	m_DirectionalLight->m_diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
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

void Renderer::RenderEntity(Camera& renderCamera, GameEntity& gameEntity)
{
	//TODO: Instead of mesh component, it could be set to some more abstract component, like RenderComponent
	if (gameEntity.HasComponent<MeshComponent>())
	{
		auto& meshComponent = gameEntity.GetComponent<MeshComponent>();

		Material& material = meshComponent.GetMaterial();
		Shader& shader = material.GetShader();
		shader.Bind();
		glBindVertexArray(meshComponent.GetVAO());

		if (m_DirectionalLight)
		{
			shader.SetUniform3f("viewPos", renderCamera.GetPosition().x, renderCamera.GetPosition().y, renderCamera.GetPosition().z);
			shader.SetUniform3f("directionLight.direction", m_DirectionalLight->GetLightDirection().x, m_DirectionalLight->GetLightDirection().y, m_DirectionalLight->GetLightDirection().z);
			shader.SetUniform3f("directionLight.ambient", m_DirectionalLight->m_ambientColor.x, m_DirectionalLight->m_ambientColor.y, m_DirectionalLight->m_ambientColor.z);
			shader.SetUniform3f("directionLight.diffuse", m_DirectionalLight->m_diffuseColor.x, m_DirectionalLight->m_diffuseColor.y, m_DirectionalLight->m_diffuseColor.z);
			shader.SetUniform3f("directionLight.specular", m_DirectionalLight->m_specularColor.x, m_DirectionalLight->m_specularColor.y, m_DirectionalLight->m_specularColor.z);
			
			if (material.GetAlbedoTexture())
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, material.GetAlbedoTexture()->GetTextureID());
				shader.SetUniform1i("material.diffuse", 0);
			}
			if (material.GetSpecularTexture())
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, material.GetSpecularTexture()->GetTextureID());
				shader.SetUniform1i("material.specular", 1);
				shader.SetUniform1i("bUseSpecular", material.IsUsingSpecularTexture());
				shader.SetUniform1f("material.shininess", 64);
			}
		}

		if (gameEntity.m_PointLight)
		{
			const PointLight& pointLight = *gameEntity.m_PointLight;

			shader.SetUniform3f("pLight.position", pointLight.RootComponent->GetPosition().x, pointLight.RootComponent->GetPosition().y, pointLight.RootComponent->GetPosition().z);
			shader.SetUniform3f("pLight.ambient", pointLight.m_ambientColor.x, pointLight.m_ambientColor.y, pointLight.m_ambientColor.z);
			shader.SetUniform3f("pLight.diffuse", pointLight.m_diffuseColor.x, pointLight.m_diffuseColor.y, pointLight.m_diffuseColor.z);
			shader.SetUniform3f("pLight.specular", pointLight.m_specularColor.x, pointLight.m_specularColor.y, pointLight.m_specularColor.z);
			shader.SetUniform1f("pLight.constant", pointLight.m_constant);
			shader.SetUniform1f("pLight.linear", pointLight.m_linear);
			shader.SetUniform1f("pLight.quadratic", pointLight.m_quadratic);
		}

		//Set MVP matrix
		shader.SetUniformMat4("model", gameEntity.GetModel());
		shader.SetUniformMat4("view", renderCamera.GetView());
		//Maybe the projection should come from the camera, as we could render in the screen multiple stuff from multiple cameras. 
		shader.SetUniformMat4("projection", projectionMat);		

		//TODO: Declare the draw function with flags so change draw parameters
		glDrawElements(GL_TRIANGLES, meshComponent.GetIndices().size(), GL_UNSIGNED_INT, 0);
	}

	
}

void Renderer::DrawGrid(Camera& renderCamera)
{
	Shader& shader = m_sceneGrid->GetShader();
	shader.Bind();
	glm::mat4 model(1.0f);
	//Set MVP matrix
	shader.SetUniformMat4("model", model);
	shader.SetUniformMat4("view", renderCamera.GetView());
	//Maybe the projection should come from the camera, as we could render in the screen multiple stuff from multiple cameras. 
	shader.SetUniformMat4("projection", projectionMat);

	m_sceneGrid->DrawGrid();
}

void Renderer::DrawScene(Viewport& viewport)
{
	DrawGrid(viewport.GetGamera());

	for (auto& gameEntity : viewport.GetGameEntities())
	{
		RenderEntity(viewport.GetGamera(), *gameEntity);
	}
}

void Renderer::SetProjectionMatrix(Camera& renderCamera, float aspectRatio)
{
	projectionMat = glm::mat4(1.0f);
	projectionMat = glm::perspective(glm::radians(renderCamera.FOV), aspectRatio, renderCamera.GetNearPlane(), renderCamera.GetFarPlane());
}

