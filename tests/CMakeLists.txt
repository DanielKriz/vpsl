cmake_minimum_required(VERSION 3.25...3.30 FATAL_ERROR)
project(
    TestRuntime
    LANGUAGES CXX C
)

set(test_exe_name "run_tests")
set(test_dir "${CMAKE_CURRENT_SOURCE_DIR}")
set(root_dir "${CMAKE_CURRENT_SOURCE_DIR}/..")

message(STATUS "Creating test executable '${test_exe_name}'")
message(STATUS "    Looking for test in ${test_dir}")
file(GLOB_RECURSE test_src_files "${test_dir}/*.cpp" "${test_dir}/**/*.cpp")
file(GLOB_RECURSE test_hdr_files "${test_dir}/*.hpp" "${test_dir}/**/*.hpp")
file(GLOB_RECURSE src_files "${root_dir}/src/*.cpp" "${root_dir}/src/**/*.cpp")
file(GLOB_RECURSE inl_files "${root_dir}/src/*.hpp" "${root_dir}/src/**/*.hpp")
file(GLOB_RECURSE hdr_files "${root_dir}/include/*.hpp" "${test_dir}/include/**/*.hpp")

list(FILTER src_files EXCLUDE REGEX ".*main\\.cpp$")

find_package(doctest REQUIRED)
include(doctest)
include(CTest)
enable_testing()

add_executable(
    ${test_exe_name}
    ${test_src_files}
    ${test_hdr_files}
    ${src_files}
    ${inl_files}
    ${hdr_files}
)

set_target_properties(
    ${test_exe_name}
    PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(${test_exe_name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(
    ${test_exe_name} PRIVATE 
    glad::glad
    glslang::glslang
    doctest::doctest
    glm::glm
    fmt::fmt
    re2::re2
    assimp
    SPIRV-Tools
    SPIRV-Tools-opt
    glslang
    glslang-default-resource-limits
    SDL2_image::SDL2_image
    SDL2::SDL2
    spdlog::spdlog
)
doctest_discover_tests(${test_exe_name})
message(STATUS "Creating test executable '${test_exe_name}' - Done")
