# CMakeList.txt : CMake project for FinalProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (FinalProject "FinalProject.cpp" "FinalProject.h")
target_include_directories(FinalProject PUBLIC "C:\\Users\\harry\\source\\repos\\FinalProject\\nana_1.7.4\\nana\\include")

add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)


target_link_directories(FinalProject PUBLIC "C:\\Users\\harry\\source\\repos\\FinalProject\\nana_1.7.4\\nana\\build\\bin")
target_link_libraries(FinalProject "nana_v142_Debug_x64")




# TODO: Add tests and install targets if needed.
