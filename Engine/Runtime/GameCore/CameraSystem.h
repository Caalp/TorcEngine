#include "Graphics/RPI/Camera.h"
#include "Core/BaseTypes.h"

#include <unordered_map>

typedef uint64 CameraID;
class Camera;

class CameraSystem
{
public:
	bool AddCamera(Camera* camera);
	bool RemoveCamera(Camera* camera);
	bool RemoveCamera(CameraID camera);
	void SetActiveCameraByID(CameraID cameraID);
	Camera* GetCameraByID(CameraID cameraID);
	CameraID GetCameraID(Camera* camera);
	Camera* GetActiveCamera();

	void Update(float dt);
private:
	std::unordered_map<CameraID, Camera*> m_camerasMap;
	CameraID m_activeCamera;
};