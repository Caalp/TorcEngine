# UnitTests/CMakeLists.txt
message(STATUS "PROCESSING ${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE UNIT_TESTS_SRCS *.cpp *h)
print_list("${UNIT_TESTS_SRCS}")

# in orde to capture entire folder tree in visual studio
GROUP_SRC("${UNIT_TESTS_SRCS}")

add_executable(UnitTests "${UNIT_TESTS_SRCS}")

find_package(Catch2 REQUIRED PATHS "${CMAKE_SOURCE_DIR}/TorcEngine/ThirdParty/Catch2")
target_link_libraries(UnitTests PRIVATE Catch2::Catch2WithMain)
target_include_directories(UnitTests PUBLIC "${CMAKE_SOURCE_DIR}/TorcEngine/ThirdParty/Catch2/include")
target_include_directories(UnitTests PUBLIC "${CMAKE_SOURCE_DIR}/TorcEngine/ThirdParty")
target_include_directories(UnitTests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# link engine with executable
target_link_libraries(UnitTests PRIVATE TorcEngine)

include(CTest)
include(Catch)
catch_discover_tests(UnitTests)