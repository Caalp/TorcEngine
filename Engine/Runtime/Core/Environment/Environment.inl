
namespace Torc
{
	namespace Core
	{
		template<typename T>
		inline EnvironmentVariable<T>* Environment::Instance()
		{
			return EnvironmentVariable<T>::Get();
		}
		
		template<typename T, typename ...Args>
		inline EnvironmentVariable<T>* Environment::GetOrCreate(Args ...args)
		{
			bool initialized = EnvironmentVariable<T>::IsInitialized();
			if (!initialized)
			{
				// create an instance and return. Just have to be carefull about thread safety here
				return EnvironmentVariable<T>::Init(args...);
			}

			// since already have an instance, just return it
			return EnvironmentVariable<T>::Get();
		}
		
		template<typename T>
		inline EnvironmentVariable<T>* Environment::Register(T* instance)
		{
			return nullptr;
		}
		
		template<typename T>
		inline EnvironmentVariable<T>* Environment::Unregister(T* instance)
		{
			return nullptr;
		}
		
		template<typename T>
		inline void Environment::Destroy()
		{
			// check if there is a valid instance, if so release it
			// otherwise nothing to do really
			if (!EnvironmentVariable<T>::IsInitialized())
			{
				return;
			}
			EnvironmentVariable<T>* evar = EnvironmentVariable<T>::Get();
			T* var = (*evar).m_variable;
			if (var)
			{
				delete var;
				(*evar).m_variable = nullptr;
			}
			delete evar;
			(*evar).m_instance = nullptr;
		}
	}
}
