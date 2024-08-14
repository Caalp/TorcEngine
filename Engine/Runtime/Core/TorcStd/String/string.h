#pragma once
#include "Core/Base.h"
#include "Core/Platform/Platform.h"

#include <string>

namespace TorcStd
{
	using string = std::string;
}

// TODO(cagri): We need another main class for String rather than templated one

template<uint32 _SIZE>
class CString
{
public:
	CString()
	{
		Torc::Platform::MemZero(m_data, _SIZE);
	}

	CString(const char* str)
	{
		strcpy_s(m_data, str);
	}

	CString(const CString& rhs)
	{
		strcpy_s(m_data, rhs.m_data);
	}

	bool operator==(const CString& rhs)
	{
		return !strcmp(m_data, rhs.m_data);
	}

	bool operator==(const CString& rhs) const
	{
		return !strcmp(m_data, rhs.m_data);
	}

	bool operator==(const char* rhs)
	{
		return !strcmp(m_data, rhs);
	}

	const char* c_str() const
	{
		return m_data;
	}

	char* Data()
	{
		return m_data;
	}

	uint32 Length() const
	{
		return strlen(m_data);
	}

	uint32 Capacity() const
	{
		return _SIZE;
	}

	void Copy(const char* str)
	{
		strcpy_s(m_data, str);
	}

	char operator[](int idx) const
	{
		return m_data[idx];
	}

	char& operator[](int idx)
	{
		return m_data[idx];
	}

private:
	char m_data[_SIZE];
};

class FixedSizeCString : public CString<248>
{
public:
	FixedSizeCString() = default;
	FixedSizeCString(const char* str)
	{
		Copy(str);
	}
};