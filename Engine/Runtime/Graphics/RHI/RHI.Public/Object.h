#pragma once
#include <iostream>
#include <Core/Threading/Atomic.h>

namespace Torc
{
	namespace RHI
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
			typedef IntrusivePtrCountPolicy<T> CountingPolicy;

			intrusive_ptr(); // never throws
			intrusive_ptr(T* p, bool add_ref = true);

			intrusive_ptr(const intrusive_ptr& r);

			template<class Y>
			intrusive_ptr(const intrusive_ptr<Y>& r);

			~intrusive_ptr();

			intrusive_ptr& operator=(const intrusive_ptr& r);

			template<class Y>
			intrusive_ptr& operator=(const intrusive_ptr<Y>& r);
			intrusive_ptr& operator=(T* r);

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
		using RefCountedPtr = intrusive_ptr<T>;
		//! Base class for all RHI classes, which provides ref counting.
		class Object
		{
		public:
			virtual ~Object() = default;

		private:
			void add_ref();
			void release();



			core::Atomic<int32> m_refCount;
		};

		template<typename T>
		inline intrusive_ptr<T>::intrusive_ptr()
		{
		}

		template<typename T>
		inline intrusive_ptr<T>::intrusive_ptr(T* p, bool add_ref)
		{
			if (m_px)
			{
				CountingPolicy::add_ref(px);
			}
		}

		template<typename T>
		inline intrusive_ptr<T>::intrusive_ptr(const intrusive_ptr& r)
		{
		}

		template<typename T>
		inline intrusive_ptr<T>::~intrusive_ptr()
		{
			if (m_px)
			{
				CountingPolicy::Release();
			}
		}

		template<typename T>
		inline intrusive_ptr<T>& intrusive_ptr<T>::operator=(const intrusive_ptr& r)
		{
			// TODO: insert return statement here
		}

		template<typename T>
		inline intrusive_ptr<T>& intrusive_ptr<T>::operator=(T* r)
		{
			// TODO: insert return statement here
		}

		template<typename T>
		inline void intrusive_ptr<T>::reset()
		{
		}

		template<typename T>
		inline void intrusive_ptr<T>::reset(T* r)
		{
		}

		template<typename T>
		inline T& intrusive_ptr<T>::operator*() const
		{
			// TODO: insert return statement here
		}

		template<typename T>
		inline T* intrusive_ptr<T>::operator->() const
		{
			return nullptr;
		}

		template<typename T>
		inline T* intrusive_ptr<T>::get() const
		{
			return nullptr;
		}

		template<typename T>
		inline void intrusive_ptr<T>::swap(intrusive_ptr& b)
		{
			T* temp = this->m_px;
			this->m_px = b->m_px;
			b->m_px = temp;
		}
	}
}

