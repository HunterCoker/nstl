cmake_minimum_required(VERSION 3.26)
project(nstl)

set(CMAKE_CXX_STANDARD 17)

add_executable(nstl main.cpp)


target_include_directories(${PROJECT_NAME}
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
