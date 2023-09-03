#pragma once
#include "Commands.h"
#include <cstdint>

typedef void* CommandPacket;
namespace commandPacket
{
	static const size_t OFFSET_NEXT_COMMAND_PACKET = 0u;
	static const size_t OFFSET_BACKEND_DISPATCH_FUNCTION = OFFSET_NEXT_COMMAND_PACKET + sizeof(CommandPacket);
	static const size_t OFFSET_COMMAND = OFFSET_BACKEND_DISPATCH_FUNCTION + sizeof(BackendDispatchFunction);
	
	/**
	 * Creates a command packet for given type of command T
	 * 
	 * @param auxMemorySize memory needed if any additional data needs to be stored within command
	 * @return returns newly created command packet
	 */
	template<typename T>
	CommandPacket Create(size_t auxMemorySize)
	{
		return ::operator new (GetSize<T>(auxMemorySize));
	}

	/**
	 * Calculate and return size of the command packet in bytes format
	 * 
	 * @param auxMemorySize additional memory used by command if any 
	 * @return total size of command packet in bytes
	 */
	template <typename T>
	size_t GetSize(size_t auxMemorySize)
	{
		return OFFSET_COMMAND + sizeof(T) + auxMemorySize;
	}

	/**
	 * Given CommandPacket moves pointer to beginning of memory block which contains
	 * the command structures and returns pointer to this region.
	 *
	 * @param packet Contiguous block of memory which contains the command
	 * @return pointer to the command
	 */
	template <typename T>
	T* GetCommand(CommandPacket packet)
	{
		return reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(packet) + OFFSET_COMMAND);
	}

	/**
	 * Given the command packet return pointer to the next command packet
	 * Pointer to the next command packet is stored in the first 4/8 bytes of the structure
	 * 
	 * @param packet Packet that stores pointer to the next command packet
	 * @return pointer to the next command packet
	 */
	CommandPacket* GetNextCommandPacket(CommandPacket packet)
	{
		return reinterpret_cast<CommandPacket*>(reinterpret_cast<uint8_t*>(packet) + OFFSET_NEXT_COMMAND_PACKET);
	}

	/**
	 * Given the pointer to a command return beginning of command packet, essentially moving pointer
	 * at the beginning of the memory region where command packet is stored
	 */
	CommandPacket* GetCommandPacketFromCommand(void* command)
	{
		return reinterpret_cast<CommandPacket*>(reinterpret_cast<uint8_t*>(command) - OFFSET_COMMAND);
	}

	/**
	 * Initializes the next command packet pointer which is stored at the beginning of the packet
	 * to given next packet
	 * 
	 * @param packet Current packet that will point to the next one
	 * @param nextPacket next command packet to point
	 */
	void StoreNextCommandPacket(CommandPacket packet, CommandPacket nextPacket)
	{
		*commandPacket::GetNextCommandPacket(packet) = nextPacket;
	}
	
	/**
	 * Retrieve backend dispacth function from CommandPacket's memory block
	 * 
	 * @param packet packet that contains the function
	 * @return backend dispatch function
	 */
	BackendDispatchFunction* GetBackendDispatchFunction(CommandPacket packet)
	{
		return (BackendDispatchFunction*)(reinterpret_cast<uint8_t*>(packet) + OFFSET_BACKEND_DISPATCH_FUNCTION);
	}

	/**
	 * Set the backend dispatch function for given packet
	 * 
	 * @param packet packet to store dispatch function
	 * @param bdf pointer to backend dispatch function
	 */
	void StoreBackendDispatchFunction(CommandPacket packet, BackendDispatchFunction bdf)
	{
		*commandPacket::GetBackendDispatchFunction(packet) = bdf;
	}

	/**
	 * Retrieves command bucket from given command packet
	 * 
	 * 
	 * @param current packet to retrieve next one from
	 * @return const pointer to the next command packet
	 */
	const CommandPacket LoadNextCommandPacket(const CommandPacket packet)
	{
		return *GetNextCommandPacket(packet);
	}

	/**
	 * Const pointer to the begining of the region that contains the command
	 * 
	 * @param packet packet which contains the command
	 * @return beginning of the memory region for command
	 */
	const void* LoadCommand(const CommandPacket packet)
	{
		return (void*)(reinterpret_cast<uint8_t*>(packet) + OFFSET_COMMAND);
	}

	/**
	 * Retrives and returns const pointer to the backend dispatch function
	 * 
	 * @param packet packet that contains the function
	 * @return const pointer to the backend dispatch function
	 */
	const BackendDispatchFunction LoadBackendDispatchFunction(const  CommandPacket packet)
	{
		return *GetBackendDispatchFunction(packet);
	}
};