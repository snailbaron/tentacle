#pragma once

#include <SDL2/SDL.h>

#include <filesystem>

class BitmapFont {
public:
    BitmapFont(SDL_Renderer* renderer, const std::filesystem::path& bitmapPath);
    ~BitmapFont();

    SDL_Rect operator[](char symbol) const;
    SDL_Texture* texture() { return _texture; }

private:
    SDL_Texture* _texture;
};
