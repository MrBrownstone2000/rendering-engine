cmake_minimum_required(VERSION 3.29)
project("Engine" CXX)

set(version "1.0")

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 23)

# TODO: See this https://cmake.org/cmake/help/latest/variable/BUILD_SHARED_LIBS.html
# But need to set up Windows DLL export first...
add_library(${PROJECT_NAME} STATIC)

# Handle libraries
add_subdirectory(extern)

find_package(SDL2 REQUIRED)
if(${SDL2_FOUND})
    message(STATUS "Found SDL: ${SDL2_PREFIX}")
endif()

find_package(GLEW REQUIRED)

include(FindOpenGL)

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${IMGUI_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENIMAGEIO_LIBRARIES} Backward::Backward fastgltf OpenGL::GL OpenImageIO)

# File Globbing
file(GLOB_RECURSE sources src/**/*.cpp src/*.cpp)
file(GLOB_RECURSE public_headers include/*.hpp)

message(${IMGUI_SOURCES})
target_sources(${PROJECT_NAME} 
    PRIVATE ${sources} ${IMGUI_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Set installation directory
if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX is not set\n"
        "Default value: ${CMAKE_INSTALL_PREFIX}\n"
        "Will set it to ${CMAKE_SOURCE_DIR}/install"
    )
    set(CMAKE_INSTALL_PREFIX
        "${CMAKE_SOURCE_DIR}/install"
        CACHE PATH "Where the library will be installed to" FORCE
    )
else()
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX was already set\n"
        "Current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()

# Installing public headers (preserving folder structure)
# Headers will be in install/include/${PROJECT_NAME}/< directory_structure_in_"<root>/include" >
include(GNUInstallDirs)
foreach(header ${public_headers})
    file(RELATIVE_PATH header_file_path "${CMAKE_CURRENT_SOURCE_DIR}/include" "${header}")
    get_filename_component(header_directory_path "${header_file_path}" DIRECTORY)
    install(
        FILES ${header}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${header_directory_path}"
    )
endforeach()

# Debug suffix
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

# Installation instructions
install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"
    # these get default values from GNUInstallDirs, no need to set them
    #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
    #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    #ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    # except for public headers, as we want them to be inside a library folder
    # PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} # include/SomeLibrary
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
)

# generate and install export file
install(EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    # NAMESPACE ${namespace}::
    DESTINATION cmake
)

include(CMakePackageConfigHelpers)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${version}"
    COMPATIBILITY AnyNewerVersion
)
# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION cmake
)
# install config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION cmake
)
# generate the export targets for the build tree
# (can't say what this one is for, but so far it has been only causing me problems,
# so I stopped adding it to projects)
# export(EXPORT "${PROJECT_NAME}Targets"
#     FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake"
#     NAMESPACE ${namespace}::
#)

option(BUILD_TESTS "Enable to build unit test" ON)

if (BUILD_TESTS)
    add_subdirectory(test)
endif()

add_subdirectory(sandbox)
