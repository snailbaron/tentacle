#pragma once

#include "bitmap_font.hpp"
#include "color.hpp"
#include "geometry.hpp"

#include <SDL2/SDL.h>

#include <vector>

class Canvas {
public:
    Canvas();
    ~Canvas();

    void clear();
    void present();

    void drawMultiLine(const Point& base, const std::vector<Point>& line);
    void drawRectangle(
        const Point& position,
        const Vector& size,
        const Color& color,
        Scalar cornerRadius = 0);
    void drawFilledRectangle(
        const Point& position,
        const Vector& size,
        const Color& color,
        Scalar cornerRadius = 0);
    void drawText(const BitmapFont& font, std::string_view text);

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
};
