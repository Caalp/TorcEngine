#pragma once
#include <Core/System/ISystem.h>

struct TestClassA { int m_a = 5; };

TEST_CASE("Basic Test for Global Environment", "[Environment_Init]")
{
	int a = 5;

	using namespace Torc::Core;
	EnvironmentVariable<TestClassA>* testClassA = Environment::GetOrCreate<TestClassA>();
	(* testClassA)->m_a = 10;
	EnvironmentVariable<TestClassA>* testClassA2 = Environment::Instance<TestClassA>();
	(*testClassA)->m_a = 11;

	Environment::Destroy<TestClassA>();

	REQUIRE(a == 5);
}

TEST_CASE("Basic Test for Global Environment", "[Environment_Init2]")
{
	int a = 5;

	using namespace Torc::Core;
	EnvironmentVariable<TestClassA>* testClassA = Environment::Instance<TestClassA>();

	if (testClassA == nullptr)
	{
		testClassA = Environment::GetOrCreate<TestClassA>();
	}
	int b = (*testClassA)->m_a;

	REQUIRE(a == 5);
}
