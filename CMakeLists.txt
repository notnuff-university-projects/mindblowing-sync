cmake_minimum_required(VERSION 3.30)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

# collect all source files
file(GLOB_RECURSE COMPILATION_UNITS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c++
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
)

add_executable(lab2 ${COMPILATION_UNITS} ${HEADERS})

target_link_libraries(lab2 PRIVATE Threads::Threads)
