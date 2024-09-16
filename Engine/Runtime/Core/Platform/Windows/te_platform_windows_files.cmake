set(PLATFORM_FILES

	${CMAKE_CURRENT_LIST_DIR}/Core/Platform/Std/Threading/platform_atomic.h
	${CMAKE_CURRENT_LIST_DIR}/Core/Platform/Std/Threading/platform_atomic.cpp
	${CMAKE_CURRENT_LIST_DIR}/Core/Platform/Std/Threading/platform_mutex.h
	${CMAKE_CURRENT_LIST_DIR}/Core/Platform/Std/Threading/platform_barrier.h
	${CMAKE_CURRENT_LIST_DIR}/Core/Platform/Std/Threading/platform_condition_variable.h
	${CMAKE_CURRENT_LIST_DIR}/Core/Platform/Std/Threading/platform_thread.h
	
	${CMAKE_CURRENT_LIST_DIR}/Core/IO/FileIO.h
	${CMAKE_CURRENT_LIST_DIR}/Core/IO/FileIO.cpp

	${CMAKE_CURRENT_LIST_DIR}/Platform_Windows.cpp
	${CMAKE_CURRENT_LIST_DIR}/PlatformGamepad_XInput.cpp
	${CMAKE_CURRENT_LIST_DIR}/PlatformInput_Windows.cpp
	${CMAKE_CURRENT_LIST_DIR}/SystemInfo_Windows.cpp
	${CMAKE_CURRENT_LIST_DIR}/Window_Windows.cpp
	${CMAKE_CURRENT_LIST_DIR}/Window_Windows.h

	${CMAKE_CURRENT_LIST_DIR}/Core/System/WindowsPlatformComponent.h
	${CMAKE_CURRENT_LIST_DIR}/Core/System/WindowsPlatformComponent.cpp
)