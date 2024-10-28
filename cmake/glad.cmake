function (vp_generate_glad generated_dir)
    set(glad_dir "${generated_dir}/glad")
    set(glad_files ${glad_dir}/include/glad/glad.h ${glad_dir}/src/glad.c)
    file(MAKE_DIRECTORY ${glad_dir})

    add_custom_target(
        glad_files ALL
        DEPENDS ${glad_files}
    )
    add_custom_command(
        OUTPUT ${glad_files}
        COMMENT "Generating GLAD files"
        COMMAND glad --spec gl --out-path "${glad_dir}" --generator c
    )

    add_library(glad SHARED ${glad_files})
    add_library(vp::glad ALIAS glad)

    set_target_properties(
        glad
        PROPERTIES
        LINKER_LANGUAGE C
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs"
    )

    target_include_directories(
        glad
        PUBLIC
        $<BUILD_INTERFACE:${glad_dir}/include>
        $<INSTALL_INTERFACE:include>
    )
endfunction()
