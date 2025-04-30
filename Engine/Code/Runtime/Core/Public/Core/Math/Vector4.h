#pragma once
#include <cmath>

namespace Torc
{
	template<typename T>
	class Vector4
	{
	public:
		union
		{
			struct
			{
				T _m[4];
			};
			struct
			{
				T x, y, z, w;
			};
		};

		Vector4();
		Vector4(T _x, T _y, T _z, T _w);
		Vector4(const Vector4& rhs);
		T Dot(const Vector4& rhs) const;
		Vector4 Normalize() const;

		//! Ignores w component and calculates cross product as of two Vector3
		Vector4 Cross(const Vector4& rhs) const;
		float Length() const;

		Vector4 operator*(float val) const;
		
		template<typename E>
		friend Vector4<E> operator*(float val, const Vector4<E>& rhs);
	};

	using Vector4f = Vector4<float>;
	using Vector4i = Vector4<int>;
	using Vector4f64 = Vector4<double>;
}

#include "../Private/Core/Math/Vector4.inl"