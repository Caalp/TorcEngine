#pragma once
#include "Core/Math.h"

class Camera 
{
public:
	Camera();
	Camera(const Camera&) = delete;

	// Getter and setters for camera position
	math::Vec3f GetPosition() const;
	void SetPosition(float x, float y, float z);
	void SetPosition(math::Vec3f& v);
	
	// Camera base vectors
	math::Vec3f GetRightDirection() const;
	math::Vec3f GetUpDirection() const;
	math::Vec3f GetLookDirection() const;

	float GetNearZ() const;
	float GetFarZ() const;
	float GetAspectRatio() const;
	float GetFovY() const;
	float GetFovX() const;

	float GetNearPlaneWidth() const;
	float GetNearPlaneHeight() const;
	float GetFarPlaneWidth() const;
	float GetFarPlaneHeight() const;

	void SetCameraLens(float fY, float aspectRatio, float zn, float zf);
	void LookAt(const math::Vec3f& pos, const math::Vec3f& target, const math::Vec3f& worldUp);

	math::Matrix4x4f GetViewMatrix() const;
	math::Matrix4x4f GetProjectionMatrix() const;
	math::Matrix4x4f ViewProjectionMatrix() const;

	void Walk(float d);
	void Strafe(float d);

	//Rotation
	void Pitch(float angle);
	void RotateY(float angle);
	void Yaw(float angle);

	void UpdateViewMatrix();	
private:
	math::Vec3f m_cameraPos;
	math::Vec3f m_cameraRight;
	math::Vec3f m_cameraUp;
	math::Vec3f m_cameraLook;
	
	// Frustum properties
	float m_nearZ;
	float m_farZ;
	float m_aspectR;
	float m_fovY;
	float m_nearPlaneHeight;
	float m_farPlaneWidth;
	float m_farPlaneHeight;
	float m_nearPlaneWidth;
	// Matrices
	math::Matrix4x4f m_viewMatrix;
	math::Matrix4x4f m_projectionMatrix;
};