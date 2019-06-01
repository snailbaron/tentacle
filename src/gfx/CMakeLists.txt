add_library (gfx
    bitmap_font.cpp
    canvas.cpp
    color.cpp
)
target_link_libraries (gfx PRIVATE stdc++fs)
target_include_directories (gfx PUBLIC include)

target_link_libraries (gfx PRIVATE ecosnail-flat)
target_link_libraries (gfx PRIVATE asset-locator)
