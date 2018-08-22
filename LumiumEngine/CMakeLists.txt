# CMakeList.txt : CMake project for LumiumEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.9)
project(LumiumEngine)

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

#stb
set(STB_INCLUDE_DIR "${CMAKE_HOME_DIRECTORY}/external/stb/include")

add_library(${PROJECT_NAME} SHARED
"${LUMI_DIR}/Graphics/Buffers.hpp" "${LUMI_DIR}/Graphics/Buffers.cpp"
"${LUMI_DIR}/Graphics/Shapes/Cube.hpp" "${LUMI_DIR}/Graphics/Shapes/Cube.cpp"
"${LUMI_DIR}/Graphics/Drawable.hpp"
"${LUMI_DIR}/Graphics/Font.hpp" "${LUMI_DIR}/Graphics/Font.cpp"
"${LUMI_DIR}/Graphics/Text.hpp" "${LUMI_DIR}/Graphics/Text.cpp"
"${LUMI_DIR}/Graphics/Texture.hpp" "${LUMI_DIR}/Graphics/Texture.cpp"
"${LUMI_DIR}/Graphics/Vertex.hpp"
"${LUMI_DIR}/System/Camera.hpp" "${LUMI_DIR}/System/Camera.cpp"
"${LUMI_DIR}/System/EventManager.hpp" "${LUMI_DIR}/System/EventManager.cpp"
"${LUMI_DIR}/System/Shaders.hpp" "${LUMI_DIR}/System/Shaders.cpp"
"${LUMI_DIR}/System/Timer.hpp" "${LUMI_DIR}/System/Timer.cpp"
"${LUMI_DIR}/System/Window.hpp" "${LUMI_DIR}/System/Window.cpp"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/${PROJECT_NAME}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/${PROJECT_NAME}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/${PROJECT_NAME}/bin"
        )


# glad
set(GLAD_DIR "${CMAKE_HOME_DIRECTORY}/external/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
set_target_properties("glad" PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories("glad" PUBLIC "${GLAD_DIR}/include")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_HOME_DIRECTORY}/LumiumEngine" "${SDL2_INCLUDE_DIRS}" "${GLAD_DIR}/include" "${STB_INCLUDE_DIR}" "${CMAKE_HOME_DIRECTORY}/external/glm/include")
if(WIN32)
	target_link_libraries(${PROJECT_NAME} PUBLIC "${OPENGL_LIBRARIES}" SDL2::SDL2 SDL2::SDL2main "glad" "${CMAKE_DL_LIBS}")
else()
	target_link_libraries(${PROJECT_NAME} PUBLIC "${OPENGL_LIBRARIES}" "SDL2" "SDL2main" "glad" "${CMAKE_DL_LIBS}")
endif()

install(DIRECTORY bin 
	DESTINATION "${CMAKE_HOME_DIRECTORY}/Lumin"
	FILES_MATCHING
	PATTERN "*.dll"
	PATTERN "*.ilk" EXCLUDE
	PATTERN "*.pdb" EXCLUDE
	)