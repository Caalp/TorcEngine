#pragma once
#include <Core/Math/Vector4.h>
#include <limits>

TEST_CASE("Dot Product of Vector4", "[Vector4_Dot]")
{
	using namespace Torc;
	Vector4<float> v1 = { 1.0f, 5.0f, -1.0f, -3.0f };
	Vector4<float> v2 = { 2.0f, 1.0f, 3.0f, -2.0f };

	float d = v1.Dot(v2);

	REQUIRE(d == 10);
}

TEST_CASE("Normalize Vector4", "[Vector4_Normalize]")
{
	using namespace Torc;
	Vector4<float> v1 = { 1, 5.0f, -1.0f, -3.0f };
	Vector4<float> v2 = { 2.0f, 1.0f, 3.0f, -2.0f };

	const Vector4<float> v1Normalized = v1.Normalize();
	const Vector4<float> v2Normalized = v2.Normalize();
	
	REQUIRE((v1Normalized.Length() == 1.0f));
	REQUIRE(v2Normalized.Length() == 1.0f);
}

TEST_CASE("Cross Product of Vector4", "[Vector4_Cross]")
{
	using namespace Torc;
	Vector4<float> v1 = { 1.0f, 0.0f, 0.0f, 1.0f };
	Vector4<float> v2 = { 1.0f, 0.0f, 0.0f, 0.0f };

	Vector4<float> v1CrossV2 = v1.Cross(v2);
	
	bool check = v1CrossV2.x == 0.0f && v1CrossV2.y == 0.0f &&
		v1CrossV2.z == 0.0f && v1CrossV2.w == 1.0f;

	REQUIRE((v1CrossV2.Length() == 1.0f && check));
}

TEST_CASE("Length of Vector4", "[Vector4_Length]")
{
	using namespace Torc;
	Vector4<float> v1 = { 1.0f, 5.0f, -1.0f, -3.0f };
	Vector4<float> v2 = { 2.0f, 1.0f, 3.0f, -2.0f };

	float l1 = v1.Length();
	float l2 = v2.Length();

	REQUIRE(l1 == 6);
	REQUIRE((l2 - 4.242641f) <= std::numeric_limits<float>::epsilon());
}

TEST_CASE("Multiplication of Vector4", "[Vector4_Multiply]")
{
	using namespace Torc;
	Vector4<float> v1 = { 1.0f, 5.0f, -1.0f, -3.0f };
	Vector4<float> v2 = { 2.0f, 1.0f, 3.0f, -2.0f };

	Vector4<float> resultV1 = v1 * 2;
	Vector4<float> resultV1_2 = 2 * v1;

	Vector4<float> resultV2 = v2 * 2;
	Vector4<float> resultV2_2 = 2 * v2;

	bool checkV1 = resultV1.x == 2.0f && resultV1.y == 10.0f &&
		resultV1.z == -2.0f && resultV1.w == -6.0f;
	bool checkV1_2 = resultV1_2.x == 2.0f && resultV1_2.y == 10.0f &&
		resultV1_2.z == -2.0f && resultV1_2.w == -6.0f;
	bool checkV2 = resultV2.x == 4.0f && resultV2.y == 2.0f &&
		resultV2.z == 6.0f && resultV2.w == -4.0f;
	bool checkV2_2 = resultV2_2.x == 4.0f && resultV2_2.y == 2.0f &&
		resultV2_2.z == 6.0f && resultV2_2.w == -4.0f;

	REQUIRE((checkV1 && checkV1_2 && checkV2 && checkV2_2));
}
