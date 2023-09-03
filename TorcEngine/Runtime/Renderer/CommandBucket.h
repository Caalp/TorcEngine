#pragma once
#include "CommandPacket.h"

template <typename T>
class CommandBucket
{
	typedef T Key;
	static constexpr uint32_t m_maxKeySize = 10000;
public:

	CommandBucket()
	{
		// allocate memory for storing keys and packets


	}

	template<typename U>
	U* AddCommand(uint32_t key, size_t auxMemorySize)
	{
		// Create command packet with command type added to bucket
		CommandPacket commandPacket = commandPacket::Create<U>(auxMemorySize);

		m_keys[m_currentIndex] = key;
		m_cmdPackets[m_currentIndex] = commandPacket;
		m_currentIndex++;

		commandPacket::StoreNextCommandPacket(commandPacket, nullptr);
		commandPacket::StoreBackendDispatchFunction(commandPacket, U::backendDispatchFunc);

		return commandPacket::GetCommand<U>(commandPacket);
	}

	template<typename U>
	U* AppendCommand(void* command, size_t auxMemorySize)
	{
		// make sure we are not already pointing to a command
		// changing this pointer without releasing memory for next command if any
		// might cause memory leaks

		// Create command packet with command type added to bucket
		CommandPacket commandPacket = commandPacket::Create<U>(auxMemorySize);

		CommandPacket currentCommandPacket = commandPacket::GetCommandPacketFromCommand(command);

		commandPacket::StoreNextCommandPacket(currentCommandPacket, commandPacket);
		commandPacket::StoreNextCommandPacket(commandPacket, nullptr);
		commandPacket::StoreBackendDispatchFunction(commandPacket, U::backendDispatchFunc);

		return commandPacket::GetCommand<U>(commandPacket);
	}

	void Submit()
	{
		for (uint32_t i = 0; i < m_currentIndex; i++)
		{
			CommandPacket packet = m_cmdPackets[i];
			do
			{
				SubmitPacket(packet);
				packet = commandPacket::LoadNextCommandPacket(packet);

			} while (packet != nullptr);
		}
	}

private:

	void SubmitPacket(const CommandPacket packet)
	{
		const BackendDispatchFunction function = commandPacket::LoadBackendDispatchFunction(packet);
		const void* command = commandPacket::LoadCommand(packet);
		function(command);
	}

private:
	Key m_keys[m_maxKeySize];
	CommandPacket m_cmdPackets[m_maxKeySize];
	static uint32_t m_currentIndex;
};

template<typename T>
uint32_t CommandBucket<T>::m_currentIndex = 0u;