#pragma once
#include <ostream>
#include <type_traits>

namespace Std
{
	//! Check boost library documentation
	template<typename T>
	struct IntrusivePtrCountPolicy
	{
		static void add_ref(T* px) { px->add_ref(); }
		static void release(T* px) { px->release(); }
	};

	template<typename T>
	class intrusive_ptr
	{

	public:
		typedef T element_type;
		typedef intrusive_ptr<T> this_type;
		typedef IntrusivePtrCountPolicy<T> CountingPolicy;

		intrusive_ptr(); // never throws
		intrusive_ptr(T* p, bool add_ref = true);

		intrusive_ptr(const intrusive_ptr& r);

		~intrusive_ptr();

		intrusive_ptr& operator=(const intrusive_ptr& r);	
		intrusive_ptr& operator=(T* r);
		intrusive_ptr(intrusive_ptr&& r);
		intrusive_ptr& operator=(intrusive_ptr&& r);

		template<class Y, std::enable_if_t<std::is_convertible_v<Y, T>, bool> = true>
		intrusive_ptr(const intrusive_ptr<Y>& r)
			: m_px((T*)r.get())
		{
			if (m_px != nullptr)
			{
				intrusive_ptr<Y>::CountingPolicy::add_ref(m_px);
			}
		}

		template<class Y, std::enable_if_t<std::is_convertible_v<Y, T>, bool> = true>
		intrusive_ptr& operator=(const intrusive_ptr<Y>& r)
		{
			intrusive_ptr<Y>(r).swap(*this);
			return *this;
		}

		template<class Y, std::enable_if_t<std::is_convertible_v<Y, T>, bool> = true>
		intrusive_ptr(intrusive_ptr<Y>&& r)
		{
			m_px = (T*)r.get();
			r.m_px = 0;
		}

		template<class Y, std::enable_if_t<std::is_convertible_v<Y, T>, bool> = true>
		intrusive_ptr<T>& operator=(intrusive_ptr<Y>&& r)
		{
			m_px = (T*)r.get();
			r.m_px = 0;
			return *this;
		}

		void reset();
		void reset(T* r);

		T& operator*() const; // never throws
		T* operator->() const; // never throws
		T* get() const; // never throws

		void swap(intrusive_ptr& b); // never throws
	private:
		T* m_px;
	};

	template<class T, class U>
	bool operator==(intrusive_ptr<T> const& a, intrusive_ptr<U> const& b); // never throws

	template<class T, class U>
	bool operator!=(intrusive_ptr<T> const& a, intrusive_ptr<U> const& b); // never throws

	template<class T>
	bool operator==(intrusive_ptr<T> const& a, T* b); // never throws

	template<class T>
	bool operator!=(intrusive_ptr<T> const& a, T* b); // never throws

	template<class T>
	bool operator==(T* a, intrusive_ptr<T> const& b); // never throws

	template<class T>
	bool operator!=(T* a, intrusive_ptr<T> const& b); // never throws

	template<class T, class U>
	bool operator<(intrusive_ptr<T> const& a, intrusive_ptr<U> const& b); // never throws

	template<class T> void swap(intrusive_ptr<T>& a, intrusive_ptr<T>& b); // never throws

	template<class T> T* get_pointer(intrusive_ptr<T> const& p); // never throws

	template<class T, class U>
	intrusive_ptr<T> static_pointer_cast(intrusive_ptr<U> const& r); // never throws

	template<class T, class U>
	intrusive_ptr<T> const_pointer_cast(intrusive_ptr<U> const& r); // never throws

	template<class T, class U>
	intrusive_ptr<T> dynamic_pointer_cast(intrusive_ptr<U> const& r); // never throws

	template<class E, class T, class Y>
	std::basic_ostream<E, T>& operator<< (std::basic_ostream<E, T>& os, intrusive_ptr<Y> const& p);

	template<typename T>
	inline intrusive_ptr<T>::intrusive_ptr()
		: m_px(nullptr)
	{
	}

	template<typename T>
	inline intrusive_ptr<T>::intrusive_ptr(T* p, bool add_ref)
		: m_px(p)
	{
		if (m_px && add_ref)
		{
			CountingPolicy::add_ref(m_px);
		}
	}

	template<typename T>
	inline intrusive_ptr<T>::intrusive_ptr(const intrusive_ptr& r)
		: m_px(r.get())
	{
		if (m_px != nullptr)
		{
			CountingPolicy::add_ref(m_px);
		}
	}

	template<typename T>
	inline intrusive_ptr<T>::~intrusive_ptr()
	{
		if (m_px)
		{
			CountingPolicy::release(m_px);
		}
	}

	template<typename T>
	inline intrusive_ptr<T>& intrusive_ptr<T>::operator=(const intrusive_ptr& r)
	{
		this_type(r).swap(*this);
		return *this;
	}

	template<typename T>
	inline intrusive_ptr<T>& intrusive_ptr<T>::operator=(T* r)
	{
		this_type(r).swap(*this);
		return *this;
	}

	template<typename T>
	inline intrusive_ptr<T>::intrusive_ptr(intrusive_ptr&& r)
	{
		m_px = r.get();
		r.m_px = 0;
	}

	template<typename T>
	inline intrusive_ptr<T>& intrusive_ptr<T>::operator=(intrusive_ptr<T>&& r)
	{
		m_px = r.get();
		r.m_px = 0;
		return *this;
	}

	template<typename T>
	inline void intrusive_ptr<T>::reset()
	{
		intrusive_ptr().swap(*this);
	}

	template<typename T>
	inline void intrusive_ptr<T>::reset(T* r)
	{
		intrusive_ptr(r).swap(*this);
	}

	template<typename T>
	inline T& intrusive_ptr<T>::operator*() const
	{
		return *get();
	}

	template<typename T>
	inline T* intrusive_ptr<T>::operator->() const
	{
		return get();
	}

	template<typename T>
	inline T* intrusive_ptr<T>::get() const
	{
		return m_px;
	}

	template<typename T>
	inline void intrusive_ptr<T>::swap(intrusive_ptr& b)
	{
		T* temp = this->m_px;
		this->m_px = b.m_px;
		b.m_px = temp;
	}

	template<class T, class U>
	bool operator==(intrusive_ptr<T> const& a, intrusive_ptr<U> const& b)
	{
		return a.get() == b.get();
	}

	template<class T, class U>
	bool operator!=(intrusive_ptr<T> const& a, intrusive_ptr<U> const& b)
	{
		return a.get() != b.get();
	}

	template<class T>
	bool operator==(intrusive_ptr<T> const& a, std::nullptr_t)
	{
		return a.get() == nullptr;
	}

	template<class T>
	bool operator!=(intrusive_ptr<T> const& a, std::nullptr_t)
	{
		return a.get() != nullptr;
	}

	template<class T>
	bool operator==(intrusive_ptr<T> const& a, T* b)
	{
		return a.get() == b;
	}

	template<class T>
	bool operator!=(intrusive_ptr<T> const& a, T* b)
	{
		return a.get() != b;
	}

	template<class T>
	bool operator==(T* a, intrusive_ptr<T> const& b)
	{
		return a == b.get();
	}

	template<class T>
	bool operator!=(T* a, intrusive_ptr<T> const& b)
	{
		return a != b.get();
	}

	template<class T, class U>
	bool operator<(intrusive_ptr<T> const& a, intrusive_ptr<U> const& b)
	{
		return (uint64_t)a.get() < (uint64_t)b.get();
	}

	template<class T>
	void swap(intrusive_ptr<T>& a, intrusive_ptr<T>& b)
	{
		a.swap(b);
	}

	template<class T>
	T* get_pointer(intrusive_ptr<T> const& p)
	{
		return p.get();
	}

	template<class T, class U>
	intrusive_ptr<T> static_pointer_cast(intrusive_ptr<U> const& r)
	{
		return intrusive_ptr<T>(static_cast<T*>(r.get()));
	}

	template<class T, class U>
	intrusive_ptr<T> const_pointer_cast(intrusive_ptr<U> const& r)
	{
		return intrusive_ptr<T>(const_cast<T*>(r.get()));
	}

	template<class T, class U>
	intrusive_ptr<T> dynamic_pointer_cast(intrusive_ptr<U> const& r)
	{
		return intrusive_ptr<T>(dynamic_cast<T*>(r.get()));
	}

	template<class E, class T, class Y>
	std::basic_ostream<E, T>& operator<<(std::basic_ostream<E, T>& os, intrusive_ptr<Y> const& p)
	{
		os << p.get();
		return os;
	}
}
