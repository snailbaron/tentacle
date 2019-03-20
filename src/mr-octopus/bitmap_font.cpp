#include "bitmap_font.hpp"

#include <SDL2/SDL_image.h>

#include <cassert>

namespace fs = std::filesystem;

BitmapFont::BitmapFont(
    SDL_Renderer* renderer,
    const fs::path& bitmapPath,
    int cellWidth,
    int cellHeight,
    int bitmapWidth,
    int bitmapHeight)
{
    assert(fs::is_regular_file(bitmapPath));
    SDL_Surface* surface = IMG_Load(bitmapPath.string().c_str());
    _texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

BitmapFont::~BitmapFont()
{
    SDL_DestroyTexture(_texture);
}
