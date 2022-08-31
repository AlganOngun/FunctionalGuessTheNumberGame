cmake_minimum_required(VERSION 3.8)

project(guessTheNumber CXX)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(guessTheNumber main.cpp)
target_link_libraries(guessTheNumber ${CONAN_LIBS})
