#include <gfx/bitmap_font.hpp>

#include <SDL2/SDL_image.h>

#include <cassert>
#include <map>
#include <initializer_list>
#include <iostream>

namespace fs = std::filesystem;

namespace gfx {

namespace {

struct SymbolCoordinates {
    int row;
    int symbol;
};

class SymbolMapContainer {
public:
    SymbolMapContainer(std::initializer_list<std::string> lines)
    {
        size_t row = 0;
        for (auto line = lines.begin(); line != lines.end(); ++line, row++) {
            for (size_t symbol = 0; symbol < line->size(); symbol++) {
                _symbolCoordinates[line->at(symbol)] = {
                    static_cast<int>(row), static_cast<int>(symbol)};
            }
        }
    }

    const SymbolCoordinates& operator[](char symbol) const
    {
        return _symbolCoordinates.at(symbol);
    }

private:
    std::map<char, SymbolCoordinates> _symbolCoordinates;
};

constexpr auto CellWidth = 6;
constexpr auto CellHeight = 8;
constexpr auto WidthBorder = 1;
constexpr auto HeightBorder = 1;

SymbolMapContainer SymbolMap {
    "abcdefghijklmnopqrstuvwxyz",
    "0123456789.!?"
};

} // namespace

BitmapFont::BitmapFont(SDL_Renderer* renderer, const fs::path& bitmapPath)
    : _texture(nullptr, SDL_DestroyTexture)
{
    assert(fs::is_regular_file(bitmapPath));
    SDL_Surface* surface = IMG_Load(bitmapPath.string().c_str());
    assert(surface);
    _texture.reset(SDL_CreateTextureFromSurface(renderer, surface));
    assert(_texture);
    SDL_FreeSurface(surface);
}

int BitmapFont::charWidth() const
{
    return CellWidth;
}

int BitmapFont::charHeight() const
{
    return CellHeight;
}

SDL_Rect BitmapFont::operator[](char symbol) const
{
    auto coordinates = SymbolMap[symbol];
    return {
        coordinates.symbol * CellWidth,
        coordinates.row * CellHeight,
        CellWidth - WidthBorder,
        CellHeight - HeightBorder,
    };
}

SDL_Texture* BitmapFont::texture()
{
    return _texture.get();
}

} // namespace gfx
