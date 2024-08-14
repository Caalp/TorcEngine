#pragma once

#include <Core/Component/ECManager.h>
#include <Core/Component/Entity.h>
#include <Core/Component/Component.h>

namespace Torc
{
	namespace Test
	{
		static ECManager* s_ecManager = ECManager::GetInstance();
		struct TestComponent : Component
		{

		};

		TEST_CASE("Test Entity Component", "[Test_Entity]")
		{
			// 1. Create entity
			Entity* testEntity0 = s_ecManager->Create();
			REQUIRE((testEntity0 != nullptr && testEntity0->GetId() >= 0));
			
			// 2. Create component and assign to entity
			//TestComponent* tc0 = new TestComponent;

			//bool assignmentResult = testEntity0->AssignComponent(*tc0);
			//REQUIRE(assignmentResult == true);

			// 3. Try assigning type of component that is already exist

			// 4. Try getting component

			// 5. Try removing component

			// 6. Check if removed component is correctly removed

			// 7. Try adding same type of component that was removed

			// 8.

			// Destroy entity

			// Check if destroyed entity is correctly removed from manager

		}
	}
}
