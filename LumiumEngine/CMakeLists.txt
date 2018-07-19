# CMakeList.txt : CMake project for LumiumEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
# project(LumiumEngine) // this is technically LumiumEngine anyways, so we don't need to redefine it

# SDL2
find_package(SDL2 CONFIG REQUIRED)

# compile glad