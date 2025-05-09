function (vp_add_imgui generated_dir)
    message(STATUS "Adding ImGUI")
    include(FetchContent)

    set(imgui_dir "${generated_dir}/imgui")
    set(imgui_src_dir "${imgui_dir}/src")

    if(NOT EXISTS ${imgui_dir}/include/imgui.h)
        message(CHECK_START "Downloading ImGUI Source Code")
        file(MAKE_DIRECTORY "${generated_dir}/include")
        FetchContent_Declare(
          imgui
          GIT_REPOSITORY https://github.com/ocornut/imgui
        )
        FetchContent_Populate(
            imgui
            GIT_REPOSITORY https://github.com/ocornut/imgui
            GIT_SHALLOW true
            GIT_PROGRESS true
            SUBBUILD_DIR "${imgui_dir}"
            # The naming is off, the source dir is used in the generation phase
            # that is the reason that it is called source dir.
            BINARY_DIR "${imgui_dir}/build"
            SOURCE_DIR "${imgui_dir}/src"
        )
        message(CHECK_PASS "Done")
    else()
        message(STATUS "ImGui already present in ${imgui_dir}/include")
    endif()

    file(GLOB imgui_hdrs "${imgui_src_dir}/*.h" "${imgui_src_dir}/**/*.h")
    file(GLOB imgui_srcs "${imgui_src_dir}/*.cpp")
    file(GLOB imgui_fonts "${imgui_src_dir}/misc/fonts/*.ttf")

    file(
        COPY ${imgui_hdrs}
        DESTINATION "${imgui_dir}/include"
    )

    list(
        APPEND imgui_srcs
        ${imgui_src_dir}/backends/imgui_impl_opengl3.cpp
        ${imgui_src_dir}/backends/imgui_impl_sdl3.cpp
        ${imgui_src_dir}/backends/imgui_impl_sdlrenderer3.cpp
    )

    option(IMGUI_SHARED "Build ImGui as shared library" OFF)
    if (${IMGUI_SHARED})
        add_library(imgui SHARED ${imgui_hdrs} ${imgui_srcs} ${imgui_fonts})
    else()
        add_library(imgui STATIC ${imgui_hdrs} ${imgui_srcs} ${imgui_fonts})
    endif()
    add_library(vp::imgui ALIAS imgui)

    set_target_properties(
        imgui
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs"
    )

    # Adding SYSTEM property to these headers is hack that surpresses warnings
    # from said headers. This due to the fact that we are only consuming them,
    # thus we do not want to be alterted.
    target_include_directories(
        imgui SYSTEM PUBLIC
        $<BUILD_INTERFACE:${imgui_src_dir}>
        $<BUILD_INTERFACE:${imgui_src_dir}/backends>
        $<INSTALL_INTERFACE:include>
    )

    find_package(glad REQUIRED)
    find_package(SDL3 REQUIRED)
    target_link_libraries(imgui PUBLIC glad::glad SDL3::SDL3)
endfunction()
