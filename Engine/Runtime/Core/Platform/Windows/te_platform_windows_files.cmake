set(PLATFORM_FILES
	${CMAKE_CURRENT_LIST_DIR}/Core/IO/FileIO.h
	${CMAKE_CURRENT_LIST_DIR}/Core/IO/FileIO.cpp

	${CMAKE_CURRENT_LIST_DIR}/Platform_Windows.cpp
	${CMAKE_CURRENT_LIST_DIR}/PlatformGamepad_XInput.cpp
	${CMAKE_CURRENT_LIST_DIR}/PlatformInput_Windows.cpp
	${CMAKE_CURRENT_LIST_DIR}/SystemInfo_Windows.cpp
	${CMAKE_CURRENT_LIST_DIR}/Window_Windows.cpp
	${CMAKE_CURRENT_LIST_DIR}/Window_Windows.h

	${CMAKE_CURRENT_LIST_DIR}/Core/TorcSystem/WindowsPlatformComponent.h
	${CMAKE_CURRENT_LIST_DIR}/Core/TorcSystem/WindowsPlatformComponent.cpp
)