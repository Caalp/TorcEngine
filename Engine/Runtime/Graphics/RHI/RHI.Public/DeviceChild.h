#pragma once
#include "RHI/RHI.Public/Object.h"

namespace Torc
{
	namespace RHI
	{
		class DeviceChild : public Object
		{
		public:
			virtual int GetDevice(void** ppvDevice) = 0;

		};
	}
}
