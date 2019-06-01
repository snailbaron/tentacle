#pragma once

#include <filesystem>

namespace assets {

enum class font {
#   define FONT(NAME) NAME,
#   include <assets.inc>
#   undef FONT
};

size_t fontsCount();
std::filesystem::path path(font id);

} // namespace assets
