#pragma once
#include "Core/Base.h"
#include "Core/TorcStd/String/string.h"

namespace Torc
{
	//! Used for uniquely identifying objects, currently supported format is {8-4-4-4-12} that is 128-bits in total
	class Uuid
	{
		struct UuidValue;
	public:

		//! Expects a uuid string enclosed with curly braces "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
		Uuid(const TorcStd::string& uuidStr);

		//! Convertes UuidValue bytes to string representation
		//! will return format as xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
		TorcStd::string ToString() const;

		friend bool operator==(const Uuid& rhs, const Uuid& lhs);
	private:

		//! Given uuid string, convert it to UuidValue byte representation
		UuidValue StringToValue(const TorcStd::string& uuidStr);

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
}
