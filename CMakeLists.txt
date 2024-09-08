cmake_minimum_required(VERSION 3.10)
project(NES-EMULATOR)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Add executable target
add_executable(nes-emulator
    main.cpp
    src/cpu.cpp
)

# Link libraries (e.g., SDL2 for graphics and input)
target_link_libraries(nes-emulator SDL2)
