#pragma once
#include "Base.h"

namespace utils
{

	/* NOTE(cagri) : source for float to uint16 conversion 
	* https://stackoverflow.com/questions/1659440/32-bit-to-16-bit-floating-point-conversion
	*/
	uint32 to_uint32(const float x);
	float to_float(const uint32 x);
	float to_float(const uint16 x);
	uint16 to_uint16(const float x);
}
