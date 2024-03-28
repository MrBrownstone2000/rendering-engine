cmake_minimum_required(VERSION 3.29)

add_subdirectory(backward)
add_subdirectory(fastgltf)

set(IMGUI_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/imgui" PARENT_SCOPE)
file(GLOB _IMGUI_SOURCES_ "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp")
set(IMGUI_SOURCES "${_IMGUI_SOURCES_}" PARENT_SCOPE)
