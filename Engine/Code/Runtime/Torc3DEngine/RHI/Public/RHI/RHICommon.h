#pragma once
#include <Core/Base.h>

namespace Torc
{
	namespace RHI
	{
		typedef struct Rect {
			long m_left;
			long m_top;
			long m_right;
			long m_bottom;
		} Rect;

		typedef struct Box
		{
			uint32_t left;
			uint32_t top;
			uint32_t front;
			uint32_t right;
			uint32_t bottom;
			uint32_t back;
		} RHIBox;


		struct Range
		{
			size_t m_begin;
			size_t m_end;
		};
	}
}
