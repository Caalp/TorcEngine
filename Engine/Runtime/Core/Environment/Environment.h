#pragma once
#include "Core/Environment/EnvironmentVariable.h"

namespace Torc
{
	namespace Core
	{
		template<typename T>
		struct EnvironmentVariable;
	
		struct Environment
		{
			template<typename T>
			static EnvironmentVariable<T>* Instance();

			template<typename T, typename... Args>
			static EnvironmentVariable<T>* GetOrCreate(Args... args);

			template<typename T>
			static EnvironmentVariable<T>* Get();

			template<typename T>
			static EnvironmentVariable<T>* Register(T* instance);

			template<typename T>
			static EnvironmentVariable<T>* Unregister(T* instance);


			//! NOTE(cagri): There are some potential side effects here that need to be taken care of
			template<typename T>
			static void Destroy();
		};
	}

	template<typename T>
	struct Interface
	{
		static T* Get()
		{
			Core::EnvironmentVariable<T>* v = Core::Environment::Get<T>();
			return (*v).operator->();
		}
	};
}

#include "Core/Environment/Environment.inl"
