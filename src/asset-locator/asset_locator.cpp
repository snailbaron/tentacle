#include <asset_locator.hpp>

#include <map>
#include <string>

namespace fs = std::filesystem;

namespace assets {

namespace {

const fs::path AssetPath = "assets";

static const std::map<font, std::string> FontNames {
#   define FONT(NAME) {font::NAME, #NAME ".png"},
#   include <assets.inc>
#   undef FONT
};

} // namespace

size_t fontsCount()
{
    return FontNames.size();
}

fs::path path(font id)
{
    return AssetPath / "fonts" / FontNames.at(id);
}

} // namespace assets
