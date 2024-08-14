#include "GameCore.h"

#include "CameraSystem.h"

void GameCore::Update(float dt)
{
	m_cameraSystem->Update(dt);
}