
namespace Torc
{
	namespace Core
	{
		template<typename T>
		EnvironmentVariable<T>* EnvironmentVariable<T>::m_instance = nullptr;

		template<typename T>
		inline T* EnvironmentVariable<T>::operator->()
		{
			return m_variable;
		}

		template<typename T>
		inline bool EnvironmentVariable<T>::IsInitialized()
		{
			return EnvironmentVariable::m_instance;
		}

		template<typename T>
		template<typename... Args>
		inline EnvironmentVariable<T>* EnvironmentVariable<T>::Init(Args... args)
		{
			EnvironmentVariable::m_instance = new EnvironmentVariable<T>();
			EnvironmentVariable::m_instance->m_variable = new Type(args...);
			return EnvironmentVariable::m_instance;
		}

		template<typename T>
		inline EnvironmentVariable<T>* EnvironmentVariable<T>::Get()
		{
			return EnvironmentVariable::m_instance;
		}
	}
}
