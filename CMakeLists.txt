# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
cmake_minimum_required (VERSION 3.9)

project ("Lumi")

# Include sub-projects.
add_subdirectory ("LumiumEngine")
add_subdirectory ("Lumin")
add_dependencies("Lumin" "LumiumEngine")