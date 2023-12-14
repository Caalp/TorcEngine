#pragma once
#include <DirectXMath/DirectXMath.h>

namespace math
{
	template<typename T>
	struct Vector2
	{
		T x;
		T y;

		Vector2() = default;
		constexpr Vector2(T _x, T _y)
			: x(_x)
			, y(_y)
		{}

		Vector2(const Vector2&) = default;
		Vector2& operator=(const Vector2&) = default;
		Vector2(Vector2&&) = default;
		Vector2& operator=(Vector2&&) = default;
	};

	template<typename T>
	struct Vector3
	{
		T x;
		T y;
		T z;

		Vector3() = default;
		Vector3(T _x, T _y, T _z)
			: x(_x)
			, y(_y)
			, z(_z)
		{}

		Vector3(const Vector3&) = default;
		Vector3& operator=(const Vector3&) = default;
		Vector3(Vector3&&) = default;
		Vector3& operator=(Vector3&&) = default;
	};

	template<typename T>
	struct Vector4
	{
		T x;
		T y;
		T z;
		T w;

		Vector4() = default;
		Vector4(T _x, T _y, T _z, T _w)
			: x(_x)
			, y(_y)
			, z(_z)
			, w(_w)
		{}

		Vector4(const Vector4&) = default;
		Vector4& operator=(const Vector4&) = default;
		Vector4(Vector4&&) = default;
		Vector4& operator=(Vector4&&) = default;
	};

	template<typename T>
	struct Matrix3x3
	{
		union
		{
			struct
			{
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			float m[3][3];
		};

		Matrix3x3() = default;
		Matrix3x3(const Matrix3x3&) = default;
		Matrix3x3& operator=(const Matrix3x3&) = default;
		Matrix3x3(Matrix3x3&&) = default;
		Matrix3x3& operator=(Matrix3x3&&) = default;

		constexpr Matrix3x3(T m00, T m01, T m02,
							T m10, T m11, T m12,
							T m20, T m21, T m22) noexcept
			: _11(m00), _12(m01), _13(m02),
			_21(m10), _22(m11), _23(m12),
			_31(m20), _32(m21), _33(m22) {}

		T  operator() (size_t Row, size_t Column) const noexcept { return m[Row][Column]; }
		T& operator() (size_t Row, size_t Column) noexcept { return m[Row][Column]; }
	};

	template<typename T>
	struct Matrix4x4
	{
		union
		{
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};

		Matrix4x4() = default;
		Matrix4x4(const Matrix4x4&) = default;
		Matrix4x4& operator=(const Matrix4x4&) = default;
		Matrix4x4(Matrix4x4&&) = default;
		Matrix4x4& operator=(Matrix4x4&&) = default;

		constexpr Matrix4x4(T m00, T m01, T m02, T m03,
							T m10, T m11, T m12, T m13,
							T m20, T m21, T m22, T m23,
							T m30, T m31, T m32, T m33) noexcept
			: _11(m00), _12(m01), _13(m02), _14(m03),
			_21(m10), _22(m11), _23(m12), _24(m13),
			_31(m20), _32(m21), _33(m22), _34(m23),
			_41(m30), _42(m31), _43(m32), _44(m33) {}

		T  operator() (size_t Row, size_t Column) const noexcept { return m[Row][Column]; }
		T& operator() (size_t Row, size_t Column) noexcept { return m[Row][Column]; }
	};

	typedef Vector2<float> Vec2f;
	typedef Vector3<float> Vec3f;
	typedef Vector4<float> Vec4f;
	typedef Matrix3x3<float> Matrix3x3f;
	typedef Matrix4x4<float> Matrix4x4f;

	inline DirectX::XMVECTOR To(Vec3f v1) 
	{
		return DirectX::XMLoadFloat3(reinterpret_cast<const DirectX::XMFLOAT3*>(&v1)); 
	}

	inline void From(const DirectX::XMVECTOR& vec, Vec3f* out)
	{
		DirectX::XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(out), vec);
	}

	template<typename T>
	inline T MatrixIdentity()
	{
		return T(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

	/**
	 * Multiply first and second vector component-wise and add to the third vector
	 */
	inline void VectorMultiplyAndAdd(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, Vec3f* out)
	{
		DirectX::XMVECTOR s = To(v1);
		DirectX::XMVECTOR l = To(v2);
		DirectX::XMVECTOR p = To(v3);
		DirectX::XMStoreFloat3((DirectX::XMFLOAT3*)out, DirectX::XMVectorMultiplyAdd(s, l, p));
	}

	/**
	 * Transform given normal vector vec3 with matrix mx and store result in out vector
	 */
	inline void Vector3fTransformNormal(const Vec3f& vec3, const Matrix4x4f& mx, Vec3f* out)
	{
		DirectX::XMMATRIX r = DirectX::XMLoadFloat4x4((const DirectX::XMFLOAT4X4*)&mx);
		DirectX::XMStoreFloat3((DirectX::XMFLOAT3*)out, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3((const DirectX::XMFLOAT3*)&vec3), r));
	}

	/*
	 * Build a rotation matrix around given axis with given angle, angle is in radians in clockwise from 
	 * axis of rotation to origin
	 * Angles are measured clockwise when looking along the rotation axis toward the origin
	 */
	inline void RotationMatrixAroundAxis(const Vec3f& axis, float angle, Matrix4x4f* out)
	{
		DirectX::XMMATRIX r = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3((const DirectX::XMFLOAT3*)&axis), angle);
		DirectX::XMStoreFloat4x4((DirectX::XMFLOAT4X4*)out, r);
	}

	/**
	 * Build a rotation matrix around Y axis for given angle and store in out parameter
	 * Angle is in radians and clockwise direction from rotation axis to origin
	 * 
	 * Angles are measured clockwise when looking along the rotation axis toward the origin
	 */
	inline void RotationMatrixAroundYAxis(float angle, Matrix4x4f* out)
	{
		DirectX::XMMATRIX r = DirectX::XMMatrixRotationY(angle);
		DirectX::XMStoreFloat4x4((DirectX::XMFLOAT4X4*)out, r);
	}

	/**
	 * Builds a left-handed perspective projection matrix based on a field of view.
	 */
	inline void PerspectiveMatrixFovLeftHanded(float fovAngleY, float aspectRatio, float nearZ, float farZ, Matrix4x4f* out)
	{
		DirectX::XMMATRIX p = DirectX::XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);
		DirectX::XMStoreFloat4x4((DirectX::XMFLOAT4X4*)out, p);
	}

	/**
	 * Subtract v2 from v1 and normalize the result and store in out
	 */
	template<typename T>
	inline void Vector3SubtractAndNormalize(const Vector3<T>& v1, const Vector3<T>& v2, Vector3<T>* out)
	{
		From(DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(To(v1), To(v2))), out);
	}

	/**
	 * Take cross-product of vector v1 and v2 and store result in out
	 */
	template<typename T>
	inline void Vector3CrossProduct(const Vector3<T>& v1, const Vector3<T>& v2, Vector3<T>* out)
	{
		From(DirectX::XMVector3Cross(To(v1), To(v2)), out);
	}

	/**
	 * Take cross-product of vector v1 and v2, normalizes the result and stores in out
	 */
	template<typename T>
	inline void Vector3CrossProductNormalized(const Vector3<T>& v1, const Vector3<T>& v2, Vector3<T>* out)
	{
		From(DirectX::XMVector3Normalize(DirectX::XMVector3Cross(To(v1), To(v2))), out);
	}

	/**
	 * Take dot-product of vector v1 and v2
	 */
	template<typename T>
	inline float Vector3DotProduct(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return DirectX::XMVectorGetX(DirectX::XMVector3Dot(To(v1), To(v2)));
	}

	/**
	 * Normalize given v1 and store normalized vector in out
	 */
	template<typename T>
	inline void Vector3Normalize(const Vector3<T>& v1, Vector3<T>* out)
	{
		From(DirectX::XMVector3Normalize(To(v1)), out);
	}

	template<typename T>
	inline bool Vector3Equal(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
	}
	
	template<typename T>
	inline void MatrixMultiply(const Matrix4x4<T>& m1, const Matrix4x4<T>& m2, Matrix4x4<T>* out)
	{
		DirectX::XMMATRIX _m1 = DirectX::XMLoadFloat4x4((const DirectX::XMFLOAT4X4*)&m1);
		DirectX::XMMATRIX _m2 = DirectX::XMLoadFloat4x4((const DirectX::XMFLOAT4X4*)&m2);

		DirectX::XMStoreFloat4x4((DirectX::XMFLOAT4X4*)out, (_m1 * _m2));
	}

	template<typename T>
	inline void MatrixTranspose(const Matrix4x4<T>& m1, Matrix4x4<T>* out)
	{
		DirectX::XMMATRIX _m1 = DirectX::XMLoadFloat4x4((const DirectX::XMFLOAT4X4*)&m1);
		DirectX::XMMatrixTranspose(_m1);		

		DirectX::XMStoreFloat4x4((DirectX::XMFLOAT4X4*)out, DirectX::XMMatrixTranspose(_m1));
	}
}