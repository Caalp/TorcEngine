#pragma once

namespace TE
{
	template<class T>
	class Singleton
	{
	public:
		static T* Get();

	private:

		static T& Initialize();
		static void Release();
		static bool IsInitialized();

	private:
		static T* m_instance;
	};

	template<typename T>
	T* Singleton<T>::Get()
	{
		T* val = m_instance;
		if (val != nullptr)
		{
			return val;
		}

		T& newVal = Initialize();

		return &newVal;
	}

	template<typename T>
	T& Singleton<T>::Initialize()
	{
		if (!IsInitialized())
		{
			m_instance = new T;
		}

		return *m_instance;
	}

	template<typename T>
	void Singleton<T>::Release()
	{
		if (IsInitialized())
		{
			delete m_instance;
		}
	}

	template<typename T>
	bool Singleton<T>::IsInitialized()
	{
		return m_instance != nullptr;
	}
}