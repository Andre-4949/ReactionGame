cmake_minimum_required(VERSION 3.8)

set(This ReactionGameTest)

file(GLOB_RECURSE Sources ./*.cpp)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
        gtest_main
        ReactionGame
        ${OpenCV_LIBS}
)

add_test(
        NAME ${This}
        COMMAND ${This}
)