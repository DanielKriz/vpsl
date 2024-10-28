cmake_minimum_required(VERSION 3.25...3.30 FATAL_ERROR)
project(
    VizualizationPrototyper
    DESCRIPTION "Tool for fast prototyping of GLSL-based vizualizations"
    LANGUAGES CXX C
)

set(main_target ${PROJECT_NAME})

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
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(glm REQUIRED)

# Add custom modules to the CMake
file(GLOB modules "${CMAKE_CURRENT_SOURCE_DIR}/cmake/*.cmake")
foreach(cmake_module ${modules})
    include(${cmake_module})
endforeach()

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

vp_generate_glad(${generated_dir})
vp_add_imgui(${generated_dir})
vp_add_compiler_settings()

# Project executable setup

file(GLOB src_files src/*.cpp/ src/**/*.cpp)
file(GLOB hdr_files include/*.hpp/ include/**/*.hpp)

add_executable(${main_target} ${src_files} ${hdr_files})
target_link_libraries(
    ${main_target} PUBLIC 
    vp::imgui
    vp::glad
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    spdlog::spdlog
    glm::glm
    fmt::fmt
    glfw
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
