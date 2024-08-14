#include "Vector4.h"

namespace Torc
{
	template<typename T>
	Vector4<T>::Vector4()
		: x(0)
		, y(0)
		, z(0)
		, w(0)
	{}

	template<typename T>
	Vector4<T>::Vector4(T _x, T _y, T _z, T _w)
		: x(_x)
		, y(_y)
		, z(_z)
		, w(_w)
	{}

	template<typename T>
	Vector4<T>::Vector4(const Vector4& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		this->w = rhs.w;
	}

	template<typename T>
	inline T Vector4<T>::Dot(const Vector4& rhs) const
	{
		return { (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z) + (this->w * rhs.w) };
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::Normalize() const
	{
		float len = Length();
		return Vector4{ this->x / len, this->y / len, this->z / len, this->w / len };
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::Cross(const Vector4<T>& rhs) const
	{
		return Vector4{ (this->y * rhs.z - this->z * rhs.y), -(this->x * rhs.z - this->z * rhs.x), (this->x * rhs.y - this->y * rhs.x), (T)1 };
	}

	template<typename T>
	inline float Vector4<T>::Length() const
	{
		return std::sqrt(this->Dot(*this));
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::operator*(float val) const
	{
		return { this->x * val, this->y * val, this->z * val, this->w * val };
	}

	template<typename E>
	inline Vector4<E> operator*(float val, const Vector4<E>& rhs)
	{
		return { rhs * val };
	}
}
