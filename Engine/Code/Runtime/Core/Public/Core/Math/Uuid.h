#pragma once
#include "Core/Base.h"
#include "Core/Std/String/string.h"

namespace Torc
{
	//! Used for uniquely identifying objects, currently supported format is {8-4-4-4-12} that is 128-bits in total
	class Uuid
	{
	public:

		//! Expects a uuid string enclosed with curly braces "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
		constexpr Uuid(const char* uuidStr);

		//! Convertes UuidValue bytes to string representation
		//! will return format as xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
		Std::string ToString() const;

		friend constexpr bool operator==(const Uuid& rhs, const Uuid& lhs);

	private:
		constexpr uint8 GetHexValue(char c) const;

		constexpr char HexToChar(uint8 c) const;

		template<size_t size>
		constexpr bool CompareByteArray(const uint8(&buffer)[size], int currentByteToCompare = 0) const;

		struct UuidValue
		{
			union
			{
				uint8 m_id[16];
				struct
				{
					uint8 m_v8[4];
					uint8 m_v4[2];
					uint8 m_v4_2[2];
					uint8 m_v4_3[2];
					uint8 m_v12[6];
				};
			};
		};
		
		UuidValue m_value;
	};

	constexpr Uuid::Uuid(const char* uuidStr)
		: m_value({})
	{
		int i = 0;
		float j = 0;
		char c = *uuidStr;
		while (c != '\0')
		{
			if (uint8 hex = GetHexValue(c); hex != 0xff)
			{
				int a = (int)j;
				int shift = (((int)(j * 2) % 2) * 4);
				m_value.m_id[(int)j] = m_value.m_id[(int)j] | (hex << shift);
				j += 0.5f;
			}
			i++;
			c = *(uuidStr + i);
		}
	}

	//! friend function impl
	constexpr bool operator==(const Uuid& rhs, const Uuid& lhs)
	{
		return rhs.CompareByteArray(lhs.m_value.m_id);
	}

	constexpr uint8 Uuid::GetHexValue(char c) const
	{
		return (c <= 'f' && c >= 'a') ? 10 + (c - 'a') : (c <= 'F' && c >= 'A') ? 10 + (c - 'A') :
			(c <= '9' && c >= '0') ? (c - '0') : 0xff;
	}

	constexpr char Uuid::HexToChar(uint8 c) const
	{
		return (c >= 0 && c <= 9) ? (char)(c + '0') : (c >= 10 && c <= 15) ? (char)((c - 10) + 'A') : '\0';
	}

	template<size_t size>
	constexpr bool Uuid::CompareByteArray(const uint8(&buffer)[size], int currentByteToCompare) const
	{
		return (currentByteToCompare < size) ? (CompareByteArray(buffer, currentByteToCompare + 1) &&
												m_value.m_id[currentByteToCompare] == buffer[currentByteToCompare]) : true;
	}
}
