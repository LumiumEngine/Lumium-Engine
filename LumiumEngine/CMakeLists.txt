# CMakeList.txt : CMake project for LumiumEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.9)
# project(LumiumEngine) // this is technically LumiumEngine anyways, so we don't need to redefine it

if(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "-d")
set(LUMI_DIR "LumiumEngine")

# find OpenGL
find_package(OpenGL REQUIRED)

# SDL2
find_package(SDL2 CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED 
"${LUMI_DIR}/System/Shader.hpp" "${LUMI_DIR}/System/Shader.cpp"
"${LUMI_DIR}/System/Window.hpp" "${LUMI_DIR}/System/Window.cpp"
"${LUMI_DIR}/System/InputManager.hpp" "${LUMI_DIR}/System/InputManager.cpp"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# glad
set(GLAD_DIR "${CMAKE_HOME_DIRECTORY}/external/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PUBLIC "${GLAD_DIR}/include")

target_include_directories(${PROJECT_NAME} PUBLIC "${SDL2_INCLUDE_DIRS}" "${GLAD_DIR}/include" "${CMAKE_HOME_DIRECTORY}/external/glm/include")
if(WIN32)
	target_link_libraries(${PROJECT_NAME} PUBLIC "${OPENGL_LIBRARIES}" SDL2::SDL2 SDL2::SDL2main "glad" "${CMAKE_DL_LIBS}")
else()
	target_link_libraries(${PROJECT_NAME} PUBLIC "${OPENGL_LIBRARIES}" SDL2 SDL2main "glad" "${CMAKE_DL_LIBS}")
endif()


set_target_properties(${PROJECT_NAME} PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/${PROJECT_NAME}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/${PROJECT_NAME}/bin"
)

install(DIRECTORY bin 
	DESTINATION "${CMAKE_HOME_DIRECTORY}/Lumin"
	FILES_MATCHING
	PATTERN "*.dll"
	PATTERN "*.ilk" EXCLUDE
	PATTERN "*.pdb" EXCLUDE
	)