add_custom_target (pack-assets-task
    COMMAND pack-assets
        --source ${PROJECT_SOURCE}/assets
        --target ${PROJECT_BINARY_DIR}/assets
        --header ${PROJECT_BINARY_DIR}/generated/asset_locations.hpp
    COMMENT "pack assets"
)
