cmake_minimum_required(VERSION 3.25...3.30 FATAL_ERROR)

# Add custom modules to the CMake
file(GLOB modules "${CMAKE_CURRENT_SOURCE_DIR}/cmake/*.cmake")
foreach(cmake_module ${modules})
    include(${cmake_module})
endforeach()

vp_download_vcpkg()

project(
    VizualizationPrototyper
    DESCRIPTION "Tool for fast prototyping of GLSL-based vizualizations"
    LANGUAGES CXX C
)

# set(main_target ${PROJECT_NAME})
set(main_target "exe")

# Source: https://cliutils.gitlab.io/modern-cmake/chapters/features.html
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(
        CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE
    )
endif()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies setup
find_package(fmt REQUIRED)
find_package(re2 REQUIRED)
find_package(assimp REQUIRED)
find_package(glm REQUIRED)
find_package(glad REQUIRED)
find_package(glslang REQUIRED)

vp_add_compiler_settings()

# Project executable setup

file(GLOB src_files src/*.cpp/ src/**/*.cpp)
file(GLOB hdr_files include/*.hpp/ include/**/*.hpp)

add_executable(${main_target} ${src_files} ${hdr_files})
target_link_libraries(
    ${main_target} PUBLIC 
    glad::glad
    glslang::glslang
    re2::re2
    assimp::assimp
    glm::glm
    fmt::fmt
)
 
set_target_properties(
    ${main_target} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
)

target_include_directories(${main_target} PUBLIC include/)

# Testing
option(BUILD_TESTS "Build testing executable" OFF)
message(STATUS "Building tests - ${BUILD_TESTS}")
if (${BUILD_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif()

# Documentation
option(BUILD_DOCUMENTATION "Build Doxygen Source Code Documentation" OFF)
message(STATUS "Building Documentation - ${BUILD_DOCUMENTATION}")
if (${BUILD_DOCUMENTATION})
    vp_generate_doxygen()
endif()
