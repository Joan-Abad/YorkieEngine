#include "CameraModule.h"

CameraModule::CameraModule()
{
}

Camera* CameraModule::CreateCamera()
{
	Camera* camera = new Camera();
	
	if (camera)
		gameCameras.push_back(camera);

	return camera;
}