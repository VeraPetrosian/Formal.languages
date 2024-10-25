cmake_minimum_required(VERSION 3.1)
project(Earley)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_INSTALL_RPATH "${PROJECT_SOURCE_DIR}/bin")

find_package(GTest REQUIRED)
include_directories(Earley PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_executable(Earley src/main.cpp src/Earley.cpp src/Grammar.cpp src/Situation.cpp)

enable_testing()
add_executable(Test tests/tests.cpp src/Earley.cpp  src/Grammar.cpp src/Situation.cpp)

add_test(Test ${Testing_SOURCE_DIR}/bin/testing_game)

target_link_libraries(Test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

install (
        TARGETS Test
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)

install (
        TARGETS Earley
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)
