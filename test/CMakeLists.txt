cmake_minimum_required(VERSION 3.29)
project("EngineTest")

file(GLOB_RECURSE sources src/**/*.cpp src/*.cpp)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE ${sources}
)

add_subdirectory(extern/UnitTests)

target_link_libraries(${PROJECT_NAME} PRIVATE UnitTests Engine)
