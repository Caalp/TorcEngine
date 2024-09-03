#pragma once

namespace Std
{
	template<typename T, class Allocator>
	class sparse_set
	{
		using type = T;
		using allocator_type = Allocator;

	public:
		sparse_set(int maxV, int capacity)
			: m_maxValue(maxV)
			, m_capacity(capacity)
			, m_n(0)
		{
			m_sparse = m_allocator.allocate(maxV);
			m_dense = m_allocator.allocate(capacity);
		}

		~sparse_set()
		{
			m_allocator.deallocate(m_sparse, m_maxValue);
			m_allocator.deallocate(m_dense, m_capacity);
		}

		void Insert(type x)
		{
			EntityIDWrapper wrapID = { x };

			if (m_n >= m_capacity || wrapID.id >= (type)m_maxValue)
			{
				Expand();
			}
			m_dense[m_n] = wrapID.uid;
			m_sparse[wrapID.id] = m_n++;
		}

		bool Remove(type x)
		{
			EntityIDWrapper wrapID = { x };

			if (!HasItem(x))
			{
				return false;
			}
			type itemIndex = m_sparse[wrapID.id];

			if (m_n - 1 != itemIndex)
			{
				type lastItem = m_dense[m_n - 1];

				// find last items index in sparse set
				int i = 0;
				for (; i < m_maxValue; ++i)
				{
					if (m_sparse[i] == m_n - 1)
					{
						break;
					}
				}

				m_sparse[i] = itemIndex;
				m_dense[itemIndex] = m_dense[m_n - 1];

			}

			m_sparse[wrapID.id] = -1;
			m_dense[m_n - 1] = -1;
			--m_n;

			return true;
		}

		type Search(type x)
		{
			if (!HasItem(x))
			{
				return (type)(-1);
			}
			return m_dense[m_sparse[EntityIDWrapper{ x }.id]];
		}

		bool HasItem(type x)
		{
			EntityIDWrapper wrapID = { x };
			return m_sparse[wrapID.id] < (uint32)m_n && m_dense[m_sparse[wrapID.id]] == x;
		}

		void Clear()
		{
			m_n = 0;
		}

		int32 Size()
		{
			return m_n;
		}

		int32 Capacity()
		{
			return m_capacity;
		}

	private:
		void Expand()
		{

			int newCapacity = m_capacity * 2;
			int newMaxValue = m_maxValue * 2;

			type* newSparse = m_allocator.allocate(newMaxValue);
			type* newDense = m_allocator.allocate(newCapacity);

			Torc::Platform::MemCopy(newSparse, m_sparse, sizeof(T) * m_maxValue);
			Torc::Platform::MemCopy(newDense, m_dense, sizeof(T) * m_capacity);

			m_allocator.deallocate(m_sparse, m_maxValue);
			m_allocator.deallocate(m_dense, m_capacity);

			m_sparse = newSparse;
			m_dense = newDense;

			m_capacity = newCapacity;
			m_maxValue = newMaxValue;
		}

		void Shrink()
		{

		}

	private:
		Allocator m_allocator;
		type* m_sparse;
		type* m_dense;
		int m_n; // current size in dense
		int m_capacity; // max element count can fit into dense
		int m_maxValue; // max number of elems can be index from sparse i.e. 5 means 0..1..2..3..4 open bound
	};
}
