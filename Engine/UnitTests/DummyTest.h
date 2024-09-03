#pragma once

#include <Core/Common/Math/MathUtils.h>
#include <Core/Std/Containers/stack.h>
#include <Core/Std/Containers/queue.h>
#include <Core/Profiling/Timer.h>
#include <Core/Memory/Memory.h>
#include <Core/Math/Uuid.h>
#include <stack>
#include <queue>

#include <Core/RTTI/RttiMacros.h>
#include <Core/Component/Entity.h>
#include <Core/Component/Component.h>

#include <Core/Module/Module.h>

struct TestA
{
	TORC_RTTI(TestA, "{4A5D1388-13FD-4742-AD1B-189318EB4D2E}");
};

struct TestB : TestA
{
	TORC_RTTI(TestB, "{4A5D1388-13FD-4742-AD1B-189318EB4D2E}", TestA);
};

struct TestC
{
	TORC_RTTI(TestC, "{4A5D1388-13FD-4742-AD1B-189318EB4D2E}");
};

struct TestComp0 : Torc::Component
{
	TORC_COMPONENT(TestComp0)
};

uint32_t factorial(uint32_t number) {
	return number <= 1 ? number : factorial(number - 1) * number;
}


TEST_CASE("Factorials are computed", "[factorial]") {
	REQUIRE(factorial(1) == 1);
	REQUIRE(factorial(2) == 2);
	REQUIRE(factorial(3) == 6);
	REQUIRE(factorial(10) == 3'628'800);
}

TEST_CASE("Vec3DotProduct are computed", "[Vec3DotProduct]") {
	REQUIRE(math::Vector3DotProduct(math::Vec3f{ 1.0f, 2.0f, 3.0f }, math::Vec3f{ 5.0f, -2.0f, -10.0f }) == -29.0f);
}

TEST_CASE("Vec3DotProduct are computed", "[Uuid]") {
	static Torc::Uuid test = "{5E29ED67-64BB-4F8A-92C2-A8595DB67AE2}";
	static Torc::Uuid test2 = "{5E29ED67-64BB-4F8A-92C2-A8595DB67AE2}";
	static Torc::Uuid test3 = "{4A5D1388-13FD-4742-AD1B-189318EB4D2E}";

	bool a = test == test2;
	Std::string s0 = test.ToString();
	Std::string s1 = test2.ToString();
	Std::string s2 = test3.ToString();

	TestB b;
	bool aa = TestB::IsTypeOf<TestC>();

	Torc::Entity m_entity;
	TestComp0 testComp0;

	bool assigned = m_entity.AssignComponent(testComp0);

	bool hasComp = m_entity.HasComponent(&testComp0);

	TestComp0* tc0_2 = m_entity.GetComponent<TestComp0>();

	TestComp0* tc0_1 = m_entity.RemoveComponent<TestComp0>();

	hasComp = m_entity.HasComponent(&testComp0);

	tc0_2 = m_entity.GetComponent<TestComp0>();

	//Std::string uuidStr = test.ToString();

}

TEST_CASE("Vec3DotProduct are computed", "[RHI]") {
	

}

TEST_CASE("Math Functions", "[Test_Math]")
{
	using namespace math;
	math::Vec3f v1 = { 1.0f, 2.0f, 3.0f };
	math::Vec3f v2 = { 11.0f, 22.0f, -12.0f };

	DirectX::XMFLOAT3 vd1 = { 1.0f, 2.0f, 3.0f };
	DirectX::XMFLOAT3 vd2 = { 11.0f, 22.0f, -12.0f };

	DirectX::XMVECTOR vec1 = DirectX::XMLoadFloat3(&vd1);
	DirectX::XMVECTOR vec2 = DirectX::XMLoadFloat3(&vd2);


	float dot_result = math::Vector3DotProduct(v1, v2);
	REQUIRE(dot_result == DirectX::XMVectorGetX(DirectX::XMVector3Dot(vec1, vec2)));

	math::Vec3f normalized1;
	math::Vector3Normalize(v1, &normalized1);

	DirectX::XMVECTOR normalized2 = DirectX::XMVector3Normalize(vec1);

	// Test To
	REQUIRE(DirectX::XMVector3Equal(math::To(v1), vec1));
	math::Vec3f temp;
	From(vec1, &temp);
	REQUIRE(Vector3Equal(temp, v1));


	Vec3f v3 = { -2.0f, -5.0f, 10.f };
	Vec3f out1;
	VectorMultiplyAndAdd(v1, v3, v2, &out1);

	REQUIRE(Vector3Equal(out1, { 9.0f, 12.0f, 18.0f }));

	Matrix4x4f xm = { 1.0f, -1.0f, -5.0f, 12.0f,
					 10.0f, -10.f, -2.0f, 5.0f,
					 2.0f, 1.0f, 0.0f, 0.0f,
					 3.0f, -3.0f, 2.0f, 3.0f };

	Vector3fTransformNormal(v1, xm, &out1);

	REQUIRE(Vector3Equal(out1, { 27.0f, -18.0f, -9.0f }));

	Matrix4x4f rotMX;
	DirectX::XMFLOAT4X4 rotMX2;

	RotationMatrixAroundAxis({ 1.0f, 0.0f, 0.0f }, -0.523599f, &rotMX);
	auto matrix4x4Comp = [](Matrix4x4f mx1, Matrix4x4f mx2) -> bool
	{
		return (mx1._11 == mx2._11 && mx1._12 == mx2._12 && mx1._13 == mx2._13 && mx1._14 == mx2._14) &&
			(mx1._21 == mx2._21 && mx1._22 == mx2._22 && mx1._23 == mx2._23 && mx1._24 == mx2._24) &&
			(mx1._31 == mx2._31 && mx1._32 == mx2._32 && mx1._33 == mx2._33 && mx1._34 == mx2._34) &&
			(mx1._41 == mx2._41 && mx1._42 == mx2._42 && mx1._43 == mx2._43 && mx1._44 == mx2._44);
	};

	DirectX::XMFLOAT3 rotAxis1 = { 1.0f, 0.0f, 0.0f };
	DirectX::XMMATRIX r = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(&rotAxis1), -0.523599f);
	DirectX::XMStoreFloat4x4(&rotMX2, r);

	REQUIRE(matrix4x4Comp(rotMX, *(Matrix4x4f*)&rotMX2));


	Vector3SubtractAndNormalize(v1, v2, &out1);

	REQUIRE(Vector3Equal(out1, { -0.371390700f, -0.742781401f, 0.557086051f }));
}

struct MyStruct
{
	void Print(int a)
	{
		char buff[64];
		sprintf_s(buff, "elem %d\n", a);
		//OutputDebugStringA(buff);
	}
};

template<uint32_t _Size>
void s_size(char(&buffer)[_Size])
{
	OutputDebugStringA(buffer);
}

TEST_CASE("Test LockFree Stack", "[Test_Stack_TS]")
{

#if 0 // need fix

	constexpr int threadCount = 2;
	constexpr int elemCount = 6'400'000;
	char out[64];
	double tt;
	core::Timer timer;
	core::Thread threads[threadCount];
	static constexpr int testOpt = 1;

	int elemPerThread = elemCount / threadCount;


	Queue_CS<int> qts;
	qts.Init(elemCount);
	auto threadFunc0 = [&qts](int start, int end)
	{
		int a;
		bool enq = true;
		for (int i = start; i < end; i++)
		{
			if constexpr (testOpt == 0)
			{
				if (i < (start + end) / 2)
				{
					qts.Enqueue(i);
				}
				else
				{
					if (i % 4 == 0)
					{
						qts.Enqueue(i);
						continue;
					}
					qts.Dequeue(&a);
				}
			}
			else if constexpr (testOpt == 1)
			{
				if (i % 2 == 0)
				{
					qts.Enqueue(i);
				}
				else
				{
					qts.Dequeue(&a);
				}
			}
			else if constexpr (testOpt == 2)
			{
				if (enq)
				{
					qts.Enqueue(i);
				}
				if (i == end - 1)
				{
					if (enq)
					{
						i = start;
					}
					enq = false;
				}
				if (!enq)
				{
					qts.Dequeue(&a);
				}
			}

		}
	};

	for (int i = 0; i < threadCount; i++)
	{
		printf("Current Thread %d started at range: %d - %d\n", i, i * elemPerThread, ((i + 1) * elemPerThread + ((i == threadCount - 1) ? (elemCount % threadCount) : 0)));
		threads[i].Start(threadFunc0, i * elemPerThread, ((i + 1) * elemPerThread + ((i == threadCount - 1) ? (elemCount % threadCount) : 0)));
	}

	timer.Start();
	for (int i = 0; i < threadCount; i++)
	{
		threads[i].WaitToFinish();
	}
	
	tt = timer.Elapsed() / 1000.0;
	//printf("Time taken with %d threads tss: %f\n", threadCount, tt);
	sprintf_s(out, "Time taken with %d threads tss: %f\n", threadCount, tt);
	//printf("Time taken with %d threads std::stack: %f\n", 1, tt);
	OutputDebugStringA(out);


	std::mutex mtex;
	std::queue<int> q1;
	timer.Start();

	auto threadFunc1 = [&q1, &mtex](int start, int end)
	{
		int a;
		bool enq = true;
		for (int i = start; i < end; i++)
		{
			if constexpr (testOpt == 0)
			{
				if (i < (start + end) / 2)
				{
					mtex.lock();
					q1.push(i);
					mtex.unlock();
				}
				else
				{
					if (i % 4 == 0)
					{
						mtex.lock();
						q1.push(i);
						mtex.unlock();
						continue;
					}
					mtex.lock();
					a = q1.front();
					q1.pop();
					mtex.unlock();
				}
			}
			else if constexpr (testOpt == 1)
			{
				if (i % 2 == 0)
				{
					mtex.lock();
					q1.push(i);
					mtex.unlock();
				}
				else
				{
					mtex.lock();
					a = q1.front();
					q1.pop();
					mtex.unlock();
				}
			}
			else if constexpr (testOpt == 2)
			{
				if (enq)
				{
					mtex.lock();
					q1.push(i);
					mtex.unlock();
				}
				if (i == end - 1)
				{
					if (enq)
					{
						i = start;
					}
					enq = false;
				}
				if (!enq)
				{
					mtex.lock();
					a = q1.front();
					q1.pop();
					mtex.unlock();
				}
			}
		}
	};

	for (int i = 0; i < threadCount; i++)
	{
		printf("Current Thread %d started at range: %d - %d\n", i, i * elemPerThread, ((i + 1) * elemPerThread + ((i == threadCount - 1) ? (elemCount % threadCount) : 0)));
		threads[i].Start(threadFunc1, i * elemPerThread, ((i + 1) * elemPerThread + ((i == threadCount - 1) ? (elemCount % threadCount) : 0)));
	}

	timer.Start();
	for (int i = 0; i < threadCount; i++)
	{
		threads[i].WaitToFinish();
	}
	tt = timer.Elapsed() / 1000.0;
	//printf("Time taken with %d threads tss: %f\n", threadCount, tt);
	sprintf_s(out, "Time taken with %d threads std::queue: %f\n", threadCount, tt);
	//printf("Time taken with %d threads std::stack: %f\n", 1, tt);
	OutputDebugStringA(out);


	Stack_TS<int> tss;
	tss.Init(elemCount);

	auto threadFunc = [&tss](int start, int end)
	{
		for (int i = start; i < end; i++)
		{

			if (i % 2 == 0)
			{
				tss.Push_TS(i);
			}
			else
			{
				tss.Pop_TS();
			}

		}
	};

	for (int i = 0; i < threadCount; i++)
	{
		printf("Current Thread %d started at range: %d - %d\n", i, i * elemPerThread, ((i + 1) * elemPerThread + ((i == threadCount - 1) ? (elemCount % threadCount) : 0)));
		threads[i].Start(threadFunc, i * elemPerThread, ((i + 1) * elemPerThread + ((i == threadCount - 1) ? (elemCount % threadCount) : 0)));
	}

	timer.StartTimer();
	for (int i = 0; i < threadCount; i++)
	{
		threads[i].WaitToFinish();
	}
	timer.StopTimer();
	tt = timer.GetElapsedTime() / 1000.0;
	//printf("Time taken with %d threads tss: %f\n", threadCount, tt);
	sprintf_s(out, "Time taken with %d threads tss: %f\n", threadCount, tt);
	//printf("Time taken with %d threads std::stack: %f\n", 1, tt);
	OutputDebugStringA(out);


	Stack_TS<int> tss2;
	tss2.Init(elemCount);

	timer.StartTimer();
	for (int i = 0; i < elemCount; i++)
	{
		if (i % 2 == 0)
		{
			tss2.Push(i);
		}
		else
		{
			tss2.Pop();
		}
	}
	timer.StopTimer();
	tt = timer.GetElapsedTime() / 1000.0;
	sprintf_s(out, "Time taken with %d threads tss2: %f\n", 1, tt);
	OutputDebugStringA(out);

	Stack_CS<int> tss3;
	tss3.Init(elemCount);

	timer.StartTimer();
	for (int i = 0; i < elemCount; i++)
	{
		if (i % 2 == 0)
		{
			tss3.Push(i);
		}
		else
		{
			tss3.Pop();
		}
	}
	timer.StopTimer();
	tt = timer.GetElapsedTime() / 1000.0;
	sprintf_s(out, "Time taken with %d threads tss3: %f\n", 1, tt);
	OutputDebugStringA(out);

	std::stack<int> stdStack;

	timer.StartTimer();
	for (int i = 0; i < elemCount; i++)
	{
		if (i % 2 == 0)
		{
			stdStack.push(i);
		}
		else
		{
			stdStack.pop();
		}
	}
	timer.StopTimer();
	tt = timer.GetElapsedTime() / 1000.0;

	sprintf_s(out, "Time taken with %d threads std::stack: %f\n", 1, tt);
	OutputDebugStringA(out);

	Stack_CS<int> tss4;
	tss4.Init(elemCount);

	auto threadFunc2 = [&tss4](int start, int end)
	{
		for (int i = start; i < end; i++)
		{
			if (i % 2 == 0)
			{
				tss4.Push(i);
			}
			else
			{
				tss4.Pop();
			}
		}
	};

	for (int i = 0; i < threadCount; i++)
	{
		threads[i].Start(threadFunc2, i * elemPerThread, ((i + 1) * elemPerThread + ((i == threadCount - 1) ? (elemCount % threadCount) : 0)));
	}

	timer.StartTimer();
	for (int i = 0; i < threadCount; i++)
	{
		threads[i].WaitToFinish();
	}
	timer.StopTimer();
	tt = timer.GetElapsedTime() / 1000.0;
	sprintf_s(out, "Time taken with %d threads tss4: %f\n", threadCount, tt);
	OutputDebugStringA(out);
#endif

}

TEST_CASE("Test FS", "[Test_FS]")
{
	//const char* file = "C:\\Users\\calp\\source\\repos\\TorcEngine\\CMakeLists.txt";
	/*std::string ext0 = fs::GetExtension(file);
	std::string dir0 = fs::GetDirectory(file);
	std::string dir1 = fs::GetParentDirectory(file);
	std::string dir2 = fs::GetParentDirectory("C:\\Users\\calp\\source\\repos\\TorcEngine\\");
	std::string dir3 = fs::GetParentDirectory(dir2.c_str());
	std::string ext1 = fs::GetFilenameWithoutExtension(file);
	std::string ext2 = fs::GetFilenameWithoutExtension(dir2.c_str());
	std::string name0 = fs::GetFilename(file);
	std::string conv0 = fs::ConvertPathSeparator("C:/Users/calp/source/repos/TorcEngine/");
	std::string conv1 = fs::ConvertPathSeparator("C:/Users/calp/source/repos/TorcEngine/", '\\');*/
}
TEST_CASE("Test Sync FileIO", "[Test_Sync_FileIO]")
{

}

//TEST_CASE("Test TypeList", "[Test_TypeList]")
//{
//	/*template<typename T0, typename... Args>
//	void TestGetFunc()
//	{
//		if (std::is_same_v<T0, NullType> || std::is_same_v<T0, TypeList<NullType>>)
//		{
//			//return;
//		}
//
//		typedef BuildTypeList<T0, Args...>::Result typeList;
//		int elemCount = GetLength<typeList>::count;
//
//		double a = 20.0;
//		typeList myList{};
//
//		auto cc = GetComponentT(myList);
//		using typee = std::conditional<true, int, double>::type;
//
//		typedef typename BuildTypeList<int, char, double>::Result mtl2;
//		//typedef typename BuildTypeList<int, double, double, double, int, char>::Result mtl2;
//		//typedef typename BuildTypeList<int, double, double, double, int, char>::Result mtl2;
//		using typee2 = Append<mtl2, float>::Result;
//
//		// NOTE typedef typename BuildTypeList<int,double, double>::Result mtl2; not compiling
//		using typee3 = GetTypeAt<mtl2, 4>::Result;
//		using typee4 = RemoveType<mtl2, uint32>::Result;
//
//		typedef typename BuildTypeList<int, char, double, double, int, char>::Result mtl3;
//		typedef typename BuildTypeList<int, double, double, double, int, char>::Result mtl4;
//		typedef typename BuildTypeList<int, double, double, double, int, char>::Result mtl5;
//		typedef typename BuildTypeList<double, double, double, int, int>::Result mtl6;
//		typedef typename BuildTypeList<double, double, double, int, int>::Result mtl7;
//		typedef typename BuildTypeList<double, double, double, int>::Result mtl8;
//		typedef typename BuildTypeList<double, double, double>::Result mtl9;
//		typedef typename BuildTypeList<double, int, char, double, double>::Result mtl10;
//
//		using typee5 = NoDuplicates<mtl3>::Result;
//		using typee6 = NoDuplicates<mtl4>::Result;
//		using typee7 = NoDuplicates<mtl5>::Result;
//		using typee8 = NoDuplicates<mtl6>::Result;
//		using typee9 = NoDuplicates<mtl7>::Result;
//		using typee10 = NoDuplicates<mtl8>::Result;
//		using typee11 = NoDuplicates<mtl9>::Result;
//		using typee12 = NoDuplicates<mtl10>::Result;
//
//		//T0* obj = GetAtIndex<2>(myList);
//		//using FrontWrapper = typename GetFront<m_tl>;
//
//		//using f = typename FrontWrapper::front;
//		//using r = NullType;//typename GetFront<FrontWrapper::rest>::front;
//		////int cc = GetLength<m_tl>::count;
//
//		//std::string tName0 = typeid(T0).name();
//		//std::string tName1 = typeid(f).name();
//		//std::string tName2 = typeid(r).name();
//		std::string tName3[14] =
//		{
//			typeid(typeList).name(),
//			typeid(typee).name(),
//			typeid(mtl2).name(),
//			typeid(typee2).name(),
//			typeid(typee3).name(),
//			typeid(typee4).name(),
//			typeid(typee5).name(),
//			typeid(typee6).name(),
//			typeid(typee7).name(),
//			typeid(typee8).name(),
//			typeid(typee9).name(),
//			typeid(typee10).name(),
//			typeid(typee11).name(),
//			typeid(typee12).name(),
//		};
//
//		LOG_INFO(LogChannel::LC_Core, "type: %s", typeid(T0).name());
//		//TestGetFunc<f, r>();
//
//	}*/
//}