cmake_minimum_required(VERSION 3.28)
set(this ReactionGame)
project(${this})

# set values

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_DEFAULT 23)

file(GLOB_RECURSE SRC include/*.h include/*.hpp src/*/*.cpp)
# get value from environmental variables
if (NOT "$ENV{OPEN_CV_PATH}" STREQUAL "")
    set(OpenCV_DIR "$ENV{OPEN_CV_PATH}" CACHE INTERNAL "Acquired opencv path from environmental variables")
else ()
    message(FATAL_ERROR "opencv has not been found, this build process requires opencv as an essential library. Please edit this CMakeLists.txt file or add the opencv folder to your environmental variables")
endif ()

include(FetchContent)
FetchContent_Declare(
        googletest
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# search package
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

add_subdirectory(test)
add_library(${this} STATIC ${SRC})
add_executable(${PROJECT_NAME}_app ${SRC} "src/main.cpp")
target_link_libraries(${PROJECT_NAME}_app ${OpenCV_LIBS} gtest)