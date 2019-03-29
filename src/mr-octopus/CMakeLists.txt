add_executable (mr-octopus
    bitmap_font.cpp
    canvas.cpp
    color.cpp
    core.cpp
    geometry.cpp
    main.cpp
    view.cpp
    widgets.cpp
)

target_link_libraries (mr-octopus PRIVATE stdc++fs)

find_package (SDL2 REQUIRED)
target_link_libraries (mr-octopus PRIVATE SDL2::SDL2)

find_library (SDL2_GFX_LIBRARY SDL2_gfx)
target_link_libraries (mr-octopus PRIVATE ${SDL2_GFX_LIBRARY})

find_path (SDL2_IMAGE_INCLUDES SDL2/SDL_image.h)
find_library (SDL2_IMAGE_LIBRARY SDL2_image)
target_include_directories (mr-octopus PRIVATE ${SDL2_IMAGE_INCLUDES})
target_link_libraries (mr-octopus PRIVATE ${SDL2_IMAGE_LIBRARY})

add_custom_command (
    TARGET mr-octopus
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "$<TARGET_FILE:mr-octopus>"
        "${PROJECT_BINARY_DIR}/$<TARGET_FILE_NAME:mr-octopus>"
)
