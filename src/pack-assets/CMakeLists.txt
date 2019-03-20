add_executable (pack-assets
    main.cpp
)

set_property (TARGET pack-assets PROPERTY CXX_STANDARD 17)
set_property (TARGET pack-assets PROPERTY CXX_STANDARD_REQUIRED TRUE)

target_link_libraries (pack-assets PRIVATE stdc++fs argo)
