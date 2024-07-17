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
    message(FATAL_ERROR "opencv has not been found, this build process requires opencv as an essential library. Please set the open cv path manually in this CMakeLists.txt under the variable name \"OpenCV_DIR\" or set OPEN_CV_PATH in your environmental variables. The path should end with \".../build/install/\".\nSetup manual for opencv:
1. create a folder for opencv\n2. Download the sourcecode for opencv from github https://github.com/opencv/opencv/releases/tag/4.10.0 to the created folder\n3. unzip the file\n4. create a build folder in the folder you created\n5. open cmake gui (download it first if you dont already have it)\n6. set sources to the unziped folder\n7. set \"where to build binaries\" on the build folder\n8. Click configure, select MinGW Makefiles and start it\n9. click generate when the process has finished\n10. switch to the build folder\n11. open a cmd in the build folder by pressing control+l and typing cmd\n12. type mingw32-make.exe install (if mingw23-make.exe has not been found, download a portable version of mingw from https://winlibs.com/ and unzip it. Search for mingw32-make.exe and retry the command with the absolute path of the portable mingw32-make.exe (put the path in quotation marks))\n\t Note: try adding \"-j4\" if you have 4 cpu cores, or try a higher number if you have even more cores\n13. In the build folder there should now be a folder named install which contains opencv\n14. Create an environmental variable named \"OPEN_CV_PATH\" which points to the install folder\n15. As a final step add \".../build/install/x64/mingw/bin\" to your windows path variable and restart your pc")
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