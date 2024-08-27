#include "Object.h"

namespace Torc
{
	namespace RHI
	{

		void Object::add_ref()
		{
			m_refCount++;
		}

		void Object::release()
		{
			int32 ref = m_refCount.Load();
			m_refCount--;
		}
	}

}
