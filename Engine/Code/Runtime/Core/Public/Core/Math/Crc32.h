#pragma once

namespace Torc
{
	class Uuid;

	class Crc32
	{
	public:
		constexpr Crc32(const Uuid& uuid)
			: m_crc(Parse(uuid))
		{
		}

	private:
		constexpr uint32_t Parse(const Uuid& uuid)
		{
			constexpr uint32_t polynomial = 0x04C11DB7;
			uint32_t crc = 0xFFFFFFFF;

			for (int i = 0; i < 16; i++)
			{
				uint8_t byte = uuid.m_value.m_id[i];
				crc ^= (uint32_t)byte << 24;
				for (int j = 0; j < 8; j++)
				{
					if (crc & 0x80000000)
					{
						crc = (crc << 1) ^ polynomial;
					}
					else
					{
						crc = crc << 1;
					}
					crc = crc & 0xFFFFFFFF;
				}
			}
			return crc ^ 0xFFFFFFFF;
		}

	private:
		uint32_t m_crc;
	};
}
