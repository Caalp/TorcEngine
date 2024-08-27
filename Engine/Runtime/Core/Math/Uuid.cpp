#include "Uuid.h"

namespace Torc
{
	TorcStd::string Uuid::ToString() const
	{
		TorcStd::string str;
		str.push_back('{');
		int i = 0;
		while (i < 16)
		{
			uint8 currentValue = m_value.m_id[i];
			str += HexToChar(currentValue & 0xf);
			str += HexToChar(((currentValue & 0xf0) >> 4));

			if (i == 3 || i == 5 || i == 7 || i == 9)
			{
				str += '-';
			}

			i++;
		}
		str.push_back('}');
		return str;
	}
}
