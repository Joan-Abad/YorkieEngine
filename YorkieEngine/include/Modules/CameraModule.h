#pragma once
#include "Camera/Camera.h"
#include <vector>

class CameraModule	
{
public:
	CameraModule();


	static CameraModule* GetInstance()
	{
		if (!instance)
			instance = new CameraModule();

		return instance;
	}

	Camera* activeCamera;
private:

	std::vector<Camera*> gameCameras;
	static CameraModule* instance;
};

