#pragma once

#include <gfx/types.hpp>

#include <SDL2/SDL.h>

#include <filesystem>
#include <memory>

namespace gfx {

class BitmapFont {
public:
    BitmapFont(SDL_Renderer* renderer, const std::filesystem::path& bitmapPath);

    int charWidth() const;
    int charHeight() const;
    SDL_Rect operator[](char symbol) const;
    SDL_Texture* texture();

private:
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> _texture;
};

} // namespace gfx
