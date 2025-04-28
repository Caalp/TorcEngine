#pragma once
#include "Base.h"

namespace Torc
{
	typedef std::pair<uint64, uint64> uint128;

	uint64 Hash64(const char* buf, size_t len);

	// Hash function for a byte array.  For convenience, a 64-bit seed is also
	// hashed into the result.
	uint64 Hash64WithSeed(const char* buf, size_t len, uint64 seed);

	// Hash function for a byte array.  For convenience, two seeds are also
	// hashed into the result.
	uint64 Hash64WithSeeds(const char* buf, size_t len,
							   uint64 seed0, uint64 seed1);

	// Hash function for a byte array.
	uint128 Hash128(const char* s, size_t len);

	// Hash function for a byte array.  For convenience, a 128-bit seed is also
	// hashed into the result.
	uint128 Hash128WithSeed(const char* s, size_t len, uint128 seed);

	// Hash function for a byte array.  Most useful in 32-bit binaries.
	uint32 Hash32(const char* buf, size_t len);
}
