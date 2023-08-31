#include "Lighting/BasicLight.h"

BasicLight::BasicLight(Viewport* viewport) : Cube(viewport), lightColor(glm::vec3(1.0,0.0,0.0))
{
	//TODO delete this pointer
	Shader* shader = new Shader("res/shaders/defaultLight.shader");
	AttachShader(shader);
	entityName = "BASIC LIGHT";

}
