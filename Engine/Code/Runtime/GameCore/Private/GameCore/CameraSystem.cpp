#include "CameraSystem.h"

bool CameraSystem::AddCamera(Camera* camera)
{
	CameraID id = reinterpret_cast<CameraID>(camera);
	if (!m_camerasMap.count(id))
	{
		m_camerasMap[id] = camera;
		return true;
	}
	return false;
}

bool CameraSystem::RemoveCamera(Camera* camera)
{
	CameraID id = reinterpret_cast<CameraID>(camera);
	if (m_camerasMap.count(id))
	{
		m_camerasMap.erase(id);
		return true;
	}
	return false;
}

bool CameraSystem::RemoveCamera(CameraID camera)
{
	if (m_camerasMap.count(camera))
	{
		m_camerasMap.erase(camera);
		return true;
	}
	return false;
}

void CameraSystem::SetActiveCameraByID(CameraID cameraID)
{
	m_activeCamera = cameraID;
}

Camera* CameraSystem::GetCameraByID(CameraID cameraID)
{
	if (auto camera = m_camerasMap.find(cameraID); camera != m_camerasMap.end())
	{
		return camera->second;
	}
	return nullptr;
}

CameraID CameraSystem::GetCameraID(Camera* camera)
{
	return reinterpret_cast<CameraID>(camera);
}

Camera* CameraSystem::GetActiveCamera()
{
	return m_camerasMap[m_activeCamera];
}

void CameraSystem::Update(float dt)
{
}