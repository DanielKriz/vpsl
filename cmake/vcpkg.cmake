function(vp_download_vcpkg)
    message(STATUS "Fetching VCPKG")
    include(FetchContent)
    FetchContent_Declare(vcpkg
        GIT_REPOSITORY https://github.com/microsoft/vcpkg/
    )
    FetchContent_MakeAvailable(vcpkg)
    set(CMAKE_TOOLCHAIN_FILE "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
    message(STATUS "    Setting the toolchain file to ${CMAKE_TOOLCHAIN_FILE}")
    message(STATUS "Fetching VCPKG - Done")
endfunction()

