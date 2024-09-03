#pragma once

namespace Std
{
	template<typename T>
	class circular_queue
	{

		using size_type = size_t;
		using value_type = T;
		using reference = T&;
		using const_reference = const T&;
		using queue = circular_queue<T>;
		using queue_reference = circular_queue<T>;
	public:

		circular_queue(uint64 capacity)
			: m_capacity(capacity)
			, m_head(0)
			, m_tail(0)
			, m_size(0)
		{
			if (m_capacity < 1)
			{
				std::cout << "Capacity of the queue cannot be less than 1\n";
			}
			m_container = new T[capacity];
		}
		~circular_queue() { delete[] container; }
		bool empty() { return m_size == 0; }
		size_type size() const { return m_size; }
		size_type capacity() const { return m_capacity; }

		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

		void push(value_type&& value)
		{
			if (isFull())
			{
				return false;
			}
			m_container[tail] = value;
			m_tail = (m_tail + 1) % m_capacity;
			m_size++;
			return true;
		}

		template<class... Args>
		void emplace(Args&&... args)
		{

		}

		void pop()
		{
			if (isEmpty())
			{
				return false;
			}
			*value = m_container[head];
			m_head = (m_head + 1) % m_capacity;
			m_size--;
			return true;
		}

		void swap(queue_reference rhs) noexcept { /* Not implemented! */ }

	private:
		T* m_container;
		uint64 m_head;
		uint64 m_tail;
		uint64 m_size;
		uint64 m_capacity;
	};
}
