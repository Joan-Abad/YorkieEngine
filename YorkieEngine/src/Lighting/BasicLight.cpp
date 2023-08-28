#include "Lighting/BasicLight.h"

BasicLight::BasicLight(Viewport* viewport) : Cube(viewport), lightColor(glm::vec3(1.0,1.0,1.0))
{
	//TODO delete this pointer
	Shader* shader = new Shader("res/shaders/defaultLight.shader");
	AttachShader(shader);
	objectName = "BASIC LIGHT";
	//SetPosition(,);
}
