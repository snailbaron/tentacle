set (fonts
    octo
)

set (asset_inc_file "${CMAKE_CURRENT_BINARY_DIR}/generated/assets.inc")
file (WRITE ${asset_inc_file})
foreach (font ${fonts})
    file (APPEND ${asset_inc_file} "FONT(${font})\n")
endforeach ()

set (asset_inc_link "${CMAKE_CURRENT_SOURCE_DIR}/include/assets.inc")
file (CREATE_LINK "${asset_inc_file}" "${asset_inc_link}" SYMBOLIC)

set (packed_asset_files)
foreach (font ${fonts})
    set (source "${PROJECT_SOURCE_DIR}/assets/fonts/${font}.aseprite")
    set (target "${PROJECT_BINARY_DIR}/assets/fonts/${font}.png")
    add_custom_command (
        OUTPUT "${target}"
        COMMAND aseprite --batch "${source}" --save-as "${target}"
        DEPENDS "${source}"
        COMMENT "converting font: ${font}"
    )
    list (APPEND packed_asset_files "${target}")
endforeach ()

add_custom_target (pack-assets
    DEPENDS "${asset_file_link}" ${packed_asset_files}
)

add_library (asset-locator
    asset_locator.cpp
)
target_link_libraries (asset-locator PRIVATE stdc++fs)
target_include_directories (asset-locator PUBLIC include)
add_dependencies (asset-locator pack-assets)
