#include "Modules/CameraModule.h"

CameraModule::CameraModule()
{
}

Camera* CameraModule::CreateCamera(Viewport* viewport)
{
	Camera* camera = new Camera(viewport);
	
	if (camera)
		gameCameras.push_back(camera);

	return camera;
}