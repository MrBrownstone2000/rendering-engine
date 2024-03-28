message( FATAL_ERROR "This is a project template, and should not be compiled or modified directly. Use the newProject.sh script to create a new project")
cmake_minimum_required(VERSION 3.29)
project("@PROJECT")

file(GLOB_RECURSE sources src/**/*.cpp src/*.cpp)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE ${sources}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Engine)
