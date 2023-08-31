#pragma once

#include "glad/glad.h"
#include "Logging/Logger.h"

//CLass meant to handle the raycast

class PickingTexture
{
public: 
	PickingTexture();
	~PickingTexture();
	void Init(unsigned int WindowWidth, unsigned int WindowHeight);
	void EnableWriting();
	void DisableWriting();

	struct PixelInfo {
		unsigned int ObjectID = 0; 
		unsigned int DrawID = 0;
		unsigned int PrimID = 0;

		void Print()
		{
			std::string log = "Object: " + std::to_string(ObjectID) + " Draw: " + std::to_string(DrawID) + ", Primitive: " + std::to_string(PrimID);
			Logger::LogInfo(log);
		}
	};

	PixelInfo ReadPixel(unsigned int x, unsigned int y);

private: 
	GLuint m_fbo = 0;
	GLuint m_pickingTexture = 0; 
	GLuint m_depthTexture = 0; 
};