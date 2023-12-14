#include "pch.h"
#include "Camera.h"

Camera::Camera() 
	: m_cameraPos(0.0f,0.0f,-30.0f)
	, m_cameraRight(1.0f,0.0f,0.0f)
	, m_cameraUp(0.0f,1.0f,0.0f)
	, m_cameraLook(0.0f,0.0f,1.0f)
	, m_nearZ(0.0f)
	, m_farZ(0.0f)
	, m_aspectR(0.0f)
	, m_fovY(0.0f)
	, m_nearPlaneHeight(0.0f)
	, m_farPlaneWidth(0.0f)
	, m_farPlaneHeight(0.0f)
	, m_nearPlaneWidth(0.0f)
	, m_viewMatrix()
	, m_projectionMatrix()
{}

math::Vec3f Camera::GetPosition() const
{
	return m_cameraPos;
}

void Camera::SetPosition(float x, float y, float z)
{
	m_cameraPos = math::Vec3f(x, y, z);
}

void Camera::SetPosition(math::Vec3f& v)
{
	m_cameraPos = v;
}

math::Vec3f Camera::GetRightDirection() const
{
	return m_cameraRight;
}

math::Vec3f Camera::GetUpDirection() const
{
	return m_cameraUp;
}

math::Vec3f Camera::GetLookDirection() const
{
	return m_cameraLook;
}

float Camera::GetNearZ() const
{
	return m_nearZ;
}

float Camera::GetFarZ() const
{
	return m_farZ;
}

float Camera::GetAspectRatio() const
{
	return m_aspectR;
}

float Camera::GetFovY() const
{
	return m_fovY;
}

float Camera::GetFovX() const
{
	float hw = 0.5f* GetNearPlaneWidth();
	return 2.0f * atanf(hw / m_nearZ);
}

float Camera::GetNearPlaneWidth() const
{
	return m_aspectR * m_nearPlaneHeight;
}

float Camera::GetNearPlaneHeight() const
{
	return m_nearPlaneHeight;
}

float Camera::GetFarPlaneWidth() const
{
	return m_aspectR * m_farPlaneHeight;
}

float Camera::GetFarPlaneHeight() const
{
	return m_farPlaneHeight;
}

void Camera::SetCameraLens(float fY, float aspectRatio, float zn, float zf)
{
	m_fovY = fY;
	m_aspectR = aspectRatio;

	m_nearZ = zn;
	m_farZ = zf;

	m_nearPlaneHeight = 2.0f * m_nearZ * tanf(0.5f * m_fovY);
	m_farPlaneHeight = 2.0f * m_farZ * tanf(0.5f* m_fovY);

	math::PerspectiveMatrixFovLeftHanded(m_fovY, m_aspectR, m_nearZ, m_farZ, &m_projectionMatrix);		

	UpdateViewMatrix();
}

void Camera::LookAt(const math::Vec3f& pos, const math::Vec3f& target, const math::Vec3f& worldUp)
{
	math::Vec3f L;
	math::Vector3SubtractAndNormalize(target, pos, &L);
	math::Vec3f R;
	Vector3CrossProductNormalized(worldUp, L, &R);

	math::Vec3f U;
	Vector3CrossProduct(L, R, &U);

	m_cameraPos = pos;
	m_cameraLook = L;
	m_cameraRight = R;
	m_cameraUp = U;
}

math::Matrix4x4f Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}

math::Matrix4x4f Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

math::Matrix4x4f Camera::ViewProjectionMatrix() const
{
	//return DirectX::XMMatrixMultiply(GetViewXM(),GetProjXM());
	return {};
}

void Camera::Walk(float d)
{
	math::VectorMultiplyAndAdd(math::Vec3f{ d, d, d }, m_cameraLook, m_cameraPos, &m_cameraPos);
}

void Camera::Strafe(float d)
{
	math::VectorMultiplyAndAdd(math::Vec3f{ d, d, d }, m_cameraRight, m_cameraPos, &m_cameraPos);
}

void Camera::Pitch(float angle)
{
	math::Matrix4x4f r2;
	math::RotationMatrixAroundAxis(m_cameraRight, angle, &r2);
	math::Vector3fTransformNormal(m_cameraUp, r2, &m_cameraUp);
	math::Vector3fTransformNormal(m_cameraLook, r2, &m_cameraLook);
}

void Camera::RotateY(float angle)
{
	math::Matrix4x4f r2;
	math::RotationMatrixAroundYAxis(angle, &r2);
	math::Vector3fTransformNormal(m_cameraUp, r2, &m_cameraUp);
	math::Vector3fTransformNormal(m_cameraLook, r2, &m_cameraLook);
	math::Vector3fTransformNormal(m_cameraRight, r2, &m_cameraRight);
}

void Camera::Yaw(float angle)
{
	math::Matrix4x4f r2;
	math::RotationMatrixAroundYAxis(angle, &r2);
	math::Vector3fTransformNormal(m_cameraUp, r2, &m_cameraUp);
	math::Vector3fTransformNormal(m_cameraLook, r2, &m_cameraLook);
	math::Vector3fTransformNormal(m_cameraRight, r2, &m_cameraRight);
}

void Camera::UpdateViewMatrix()
{
	math::Vec3f R = m_cameraRight;
	math::Vec3f U = m_cameraUp;
	math::Vec3f L = m_cameraLook;
	math::Vec3f P = m_cameraPos;

	//  Normalize look vector
	math::Vector3Normalize(L, &L);
	math::Vector3CrossProductNormalized(L, R, &U);
	math::Vector3CrossProduct(U, L, &R);

	float x = -math::Vector3DotProduct(P, R);
	float y = -math::Vector3DotProduct(P, U);
	float z = -math::Vector3DotProduct(P, L);

	m_cameraRight = R;
	m_cameraUp = U;
	m_cameraLook = L;
	
	m_viewMatrix(0, 0) = m_cameraRight.x;
	m_viewMatrix(1, 0) = m_cameraRight.y;
	m_viewMatrix(2, 0) = m_cameraRight.z;
	m_viewMatrix(3, 0) = x;

	m_viewMatrix(0, 1) = m_cameraUp.x;
	m_viewMatrix(1, 1) = m_cameraUp.y;
	m_viewMatrix(2, 1) = m_cameraUp.z;
	m_viewMatrix(3, 1) = y;

	m_viewMatrix(0, 2) = m_cameraLook.x;
	m_viewMatrix(1, 2) = m_cameraLook.y;
	m_viewMatrix(2, 2) = m_cameraLook.z;
	m_viewMatrix(3, 2) = z;

	m_viewMatrix(0, 3) = 0.0f;
	m_viewMatrix(1, 3) = 0.0f;
	m_viewMatrix(2, 3) = 0.0f;
	m_viewMatrix(3, 3) = 1.0f;
}