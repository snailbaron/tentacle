#pragma once

#include <SDL2/SDL.h>

#include <filesystem>

class BitmapFont {
    BitmapFont(
        SDL_Renderer* renderer,
        const std::filesystem::path& bitmapPath,
        int cellWidth,
        int cellHeight,
        int bitmapWidth,
        int bitmapHeight);

    ~BitmapFont();

    SDL_Rect operator[](char symbol) const;

    SDL_Texture* _texture;

    friend class Canvas;
};
