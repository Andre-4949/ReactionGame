cmake_minimum_required(VERSION 3.28)
project(ReactionGame)

# set values

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_DEFAULT 23)

file(GLOB_RECURSE SRC "include/*.h" "include/*.hpp" "src/*.cpp")
# get value from environmental variables
if (NOT "$ENV{OPEN_CV_PATH}" STREQUAL "")
    set(OpenCV_DIR "$ENV{OPEN_CV_PATH}" CACHE INTERNAL "Acquired opencv path from environmental variables")
else ()
    message(FATAL_ERROR "opencv has not been found, this build process requires opencv as an essential library. Please edit this CMakeLists.txt file or add the opencv folder to your environmental variables")
endif ()

# search package
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})