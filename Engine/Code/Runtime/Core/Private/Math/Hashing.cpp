#include "Math/Hashing.h"
#include <CityHash/city.h>

namespace Torc
{
	uint64 Hash64(const char* buf, size_t len)
	{
		return CityHash64(buf, len);
	}
	
	uint64 Hash64WithSeed(const char* buf, size_t len, uint64 seed)
	{
		return CityHash64WithSeed(buf, len, seed);
	}

	uint64 Hash64WithSeeds(const char* buf, size_t len, uint64 seed0, uint64 seed1)
	{
		return CityHash64WithSeeds(buf, len, seed0, seed1);
	}

	uint128 Hash128(const char* s, size_t len)
	{
		return CityHash128(s, len);
	}

	uint128 Hash128WithSeed(const char* s, size_t len, uint128 seed)
	{
		return CityHash128WithSeed(s, len, seed);
	}

	uint32 Hash32(const char* buf, size_t len)
	{
		return CityHash32(buf, len);
	}
}
