cmake_minimum_required(VERSION 2.6)
project(sierpinski_zoom)

find_package(GLUT)
find_package(OpenGL)

include_directories(src ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} Simple\ OpenGL\ Image\ Library/src)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-g -Wall")
add_subdirectory(src)  
add_subdirectory(Simple\ OpenGL\ Image\ Library)
