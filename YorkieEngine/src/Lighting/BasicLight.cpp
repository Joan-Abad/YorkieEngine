#include "Lighting/BasicLight.h"

BasicLight::BasicLight(const char* name) : Cube(), lightColor(glm::vec3(1.0,1.0,1.0))
{
	//TODO delete this pointer
	Shader* shader = new Shader("res/shaders/defaultLight.shader");
	AttachShader(shader);
	objectName = name;
	//SetPosition(,);
}
