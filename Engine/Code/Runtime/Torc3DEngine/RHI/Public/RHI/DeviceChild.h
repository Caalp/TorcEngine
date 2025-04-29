#pragma once
#include "RHIObject.h"

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
