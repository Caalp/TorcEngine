#pragma once

namespace Torc
{
	namespace Core
	{
		template<typename T>
		class EnvironmentVariable
		{
			friend class Environment;
			using Type = T;
		public:
			Type* operator->();

		private:
			static bool IsInitialized();

			template<typename... Args>
			static EnvironmentVariable<Type>* Init(Args... args);

			static EnvironmentVariable* Get();
			

			T* m_variable;
			static EnvironmentVariable* m_instance;
		};
	}
}

#include "../Private/Core/Environment/EnvironmentVariable.inl"
