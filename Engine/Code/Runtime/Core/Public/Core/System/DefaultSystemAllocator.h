#pragma once

namespace Torc
{
	class DefaultSystemAllocator
	{
	public:
		template<typename T>
		static void* New(size_t size) { return ::operator new(size); }

		template<typename T>
		static void Delete(void* p) { ::operator delete(p); }
	private:
	};
}
