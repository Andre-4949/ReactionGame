cmake_minimum_required(VERSION 3.8)

set(This ReactionGameTest)

set(Sources ReactionGameTest.cpp)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
        gtest_main
        ReactionGame
)

add_test(
        NAME ${This}
        COMMAND ${This}
)
