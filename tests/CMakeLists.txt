cmake_minimum_required(VERSION 3.25...3.30 FATAL_ERROR)
project(
    TestRuntime
    LANGUAGES CXX C
)

set(test_exe_name "run_tests")
set(test_dir "${CMAKE_CURRENT_SOURCE_DIR}")

message(STATUS "Creating test executable '${test_exe_name}'")
message(STATUS "    Looking for test in ${test_dir}")
file(GLOB test_src_files "${test_dir}/*.cpp" "${test_dir}/**/*.cpp")
file(GLOB test_hdr_files "${test_dir}/*.hpp" "${test_dir}/**/*.hpp")

find_package(doctest REQUIRED)
include(doctest)
include(CTest)
enable_testing()

add_executable(
    ${test_exe_name}
    ${test_src_files}
    ${test_hdr_files}
)
set_target_properties(
    ${test_exe_name}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(${test_exe_name} PRIVATE doctest::doctest)
doctest_discover_tests(${test_exe_name})
message(STATUS "Creating test executable '${test_exe_name}' - Done")
