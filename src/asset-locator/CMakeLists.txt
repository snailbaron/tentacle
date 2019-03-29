set (asset_header_name asset_locator.hpp)
set (asset_source_name asset_locator.cpp)

set (asset_header "${CMAKE_CURRENT_BINARY_DIR}/generated/${asset_header_name}")
set (asset_source "${CMAKE_CURRENT_BINARY_DIR}/generated/${asset_source_name}")

set (asset_header_link
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${asset_header_name}")
set (asset_source_link "${CMAKE_CURRENT_SOURCE_DIR}/${asset_source_name}")

add_custom_command (
    OUTPUT "${asset_header}" "${asset_source}"
    COMMAND pack-assets
        --source-assets "${PROJECT_SOURCE_DIR}/assets"
        --target-assets "${PROJECT_BINARY_DIR}/assets"
        --header "${asset_header}"
        --source "${asset_source}"
    DEPENDS pack-assets
    COMMENT
        "generating assets: '${PROJECT_SOURCE_DIR}' -> '${PROJECT_BINARY_DIR}'\n\
    header: '${asset_header}'\n    source: '${asset_source}'"
)

add_custom_command (
    OUTPUT "${asset_header_link}"
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${asset_header}" "${asset_header_link}"
    DEPENDS "${asset_header}"
    COMMENT "creating asset header link"
)

add_custom_command (
    OUTPUT "${asset_source_link}"
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${asset_source}" "${asset_source_link}"
    DEPENDS "${asset_source}"
    COMMENT "creating asset source link"
)

add_custom_target (run-pack-assets
    DEPENDS "${asset_header_link}" "${asset_source_link}"
    COMMENT "assets custom target"
)

add_library (asset-locator
    asset_locator.cpp
)
target_include_directories (asset-locator PUBLIC include)

add_dependencies (asset-locator run-pack-assets)
