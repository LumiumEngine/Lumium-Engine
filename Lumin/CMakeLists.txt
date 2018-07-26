# CMakeList.txt : CMake project for LumiumEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.9)
project(Lumin)

set(CMAKE_DEBUG_POSTFIX "-d")

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC LumiumEngine)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_HOME_DIRECTORY}/LumiumEngine)

set_target_properties(${PROJECT_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/${PROJECT_NAME}/bin"
)