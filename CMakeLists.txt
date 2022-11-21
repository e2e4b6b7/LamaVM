cmake_minimum_required(VERSION 3.20)

project(LamaVM)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -g -DLAMA_VM_DEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

# Generate profiler data
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-generate")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-generate")

# Use profiler data
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-use")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-use")

include_directories(src)

add_executable(LamaVM src/main.cpp)

target_link_libraries(LamaVM ${CMAKE_SOURCE_DIR}/runtime/runtime.a)
