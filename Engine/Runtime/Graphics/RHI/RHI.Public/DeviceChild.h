#pragma once
#include "RHI/RHI.Public/Object.h"

namespace Torc
{
	namespace RHI
	{
		class Device;

		class DeviceChild : public RHI::Object
		{
		public:
			virtual int GetDevice(Device* ppvDevice) = 0;
		};
	}
}
