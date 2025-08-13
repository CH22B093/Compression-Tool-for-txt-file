cmake_minimum_required(VERSION 3.10)
project(AlgorithmicFileCompressor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(compressor src/compressor.cpp)
target_include_directories(compressor PUBLIC include)

add_executable(compress_tool src/main.cpp)
target_link_libraries(compress_tool PRIVATE compressor)

enable_testing()
add_subdirectory(tests)

# Fetch Catch2 for testing
include(FetchContent)
FetchContent_Declare(
	catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v2.13.8
)
FetchContent_MakeAvailable(catch2)
