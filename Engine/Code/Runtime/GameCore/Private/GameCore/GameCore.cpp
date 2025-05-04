#include "GameCore/GameCore.h"

#include "GameCore/CameraSystem.h"

void GameCore::Update(float dt)
{
	m_cameraSystem->Update(dt);
}