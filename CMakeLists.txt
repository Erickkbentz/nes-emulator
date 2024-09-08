cmake_minimum_required(VERSION 3.10)
project(NES-EMULATOR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

# Find packages
find_package(SDL2 REQUIRED)
find_package(GTest REQUIRED)

# Include directories
include_directories(include)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})

# Define source files
file(GLOB SRC_FILES "src/*.cpp")
file(GLOB TEST_FILES "tst/*.cpp")

# Add executable for the main application
add_executable(nes-emulator
    main.cpp
    ${SRC_FILES}
)

# Add test executable
add_executable(runTests
    ${TEST_FILES}
    ${SRC_FILES}
)

# Link libraries
target_link_libraries(nes-emulator ${SDL2_LIBRARIES})
target_link_libraries(runTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

add_test(NAME runTests COMMAND runTests)
