set (asset_file_name assets.inc)
set (asset_file "${CMAKE_CURRENT_BINARY_DIR}/generated/${asset_file_name}")
set (asset_file_link "${CMAKE_CURRENT_SOURCE_DIR}/include/${asset_file_name}")

add_custom_command (
    OUTPUT "${asset_file}"
    COMMAND pack-assets
        --source-assets "${PROJECT_SOURCE_DIR}/assets"
        --target-assets "${PROJECT_BINARY_DIR}/assets"
        --output "${asset_file}"
    DEPENDS pack-assets
    COMMENT "packing assets: '${PROJECT_SOURCE_DIR}' -> '${PROJECT_BINARY_DIR}'"
    COMMENT "also generating asset file: '${asset_file}'"
)

add_custom_command (
    OUTPUT "${asset_file_link}"
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${asset_file}" "${asset_file_link}"
    DEPENDS "${asset_file}"
    COMMENT "creating asset file link: '${asset_file_link}'"
)

add_custom_target (run-pack-assets
    DEPENDS "${asset_file_link}"
)

add_library (asset-locator
    asset_locator.cpp
)
target_include_directories (asset-locator PUBLIC include)

add_dependencies (asset-locator run-pack-assets)
