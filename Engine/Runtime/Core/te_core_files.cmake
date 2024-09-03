set(FILES

    Application.cpp
    Application.h
    Base.h

    # Common folder
    Common/UtilMacros.h
    Common/Utils.cpp
    Common/Utils.h
    Common/Math/MathUtils.h

    # Math folder
    Math/Vector4.h
    Math/Vector4.inl
    Math/Uuid.h
    Math/Hashing.h
    Math/Hashing.cpp
    Math/Uuid.h
    Math/Uuid.cpp

    # Component Folder
    Component/Component.h
    Component/Component.cpp
    Component/Entity.h
    Component/Entity.cpp

    # RTTI Folder
    RTTI/TypeName.h
    RTTI/TypeList.h
    RTTI/RttiMacros.h

    # Environment Folder
    Environment/Environment.h
    Environment/Environment.inl
    Environment/EnvironmentVariable.h
    Environment/EnvironmentVariable.inl


    # Input folder
    Input/BaseInput.cpp
    Input/BaseInput.h
    Input/Gamepad.cpp
    Input/Gamepad.h
    Input/Keyboard.cpp
    Input/Keyboard.h
    Input/Mouse.cpp
    Input/Mouse.h
	Input/PlatformInput.h

    # IO folder
    IO/FileIOBase.h
    IO/FileIOBase.cpp
    IO/FileStream.h
    IO/FileStream.cpp
    IO/Path/Path.h
    IO/Path/Path.cpp

    # JobSystem folder
	JobSystem/GenericTaskQueue.cpp
    JobSystem/GenericTaskQueue.h

    # Logging folder
    Logging/DebugWindowLogger.cpp
    Logging/DebugWindowLogger.h
    Logging/FileLogger.cpp
    Logging/FileLogger.h
    Logging/Logger.cpp
    Logging/Logger.h

    # Memory folder
    Memory/Allocators/PoolAllocator.cpp
    Memory/Allocators/PoolAllocator.h
    Memory/Allocators/StackAllocator.h
    Memory/Allocators/StackFrameAllocator.cpp
    Memory/Allocators/StackFrameAllocator.h
    Memory/Memory.cpp
    Memory/Memory.h
    Memory/Memory_defs.h

    # Module folder
    Module/Module.cpp
    Module/Module.h
    Module/ModuleManager.h
    Module/ModuleManager.cpp

    # TorcStd folder
    TorcStd/Containers/circular_queue.h
    TorcStd/Containers/sparse_set.h
    TorcStd/Containers/freelist.h
    TorcStd/Containers/queue.h
    TorcStd/Containers/stack.h
    TorcStd/String/string.cpp
    TorcStd/String/string.h
    TorcStd/String/string_utils.cpp
    TorcStd/String/string_utils.h
    
    # Threading folder
    Threading/Atomic.h
    Threading/Barrier.h
    Threading/ConditionVariable.h
    Threading/Mutex.cpp
    Threading/Mutex.h
    Threading/Thread.cpp
    Threading/Thread.h

    # TorcSystem folder
    TorcSystem/ISystem.h
    TorcSystem/SystemComponent.h

    # Profiling folder
    Profiling/Timer.h
    Profiling/Timer.cpp
    Profiling/SystemTimer.h
    Profiling/SystemTimer.cpp

	# Singleton
    Singleton/Singleton.h
	
	# Platform
	Platform/PlatformDefines.h
	Platform/Platform.h
	
	# SystemInfo
	SystemInfo/SystemInfo.h
	
	# Windowing
	Windowing/WindowBase.h
	Windowing/WindowBase.cpp

    # Parsers
    Parsers/JsonReader.h
)