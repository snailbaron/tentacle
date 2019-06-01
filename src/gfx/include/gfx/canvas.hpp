#pragma once

#include "bitmap_font.hpp"
#include "color.hpp"
#include "types.hpp"

#include <asset_locator.hpp>

#include <SDL2/SDL.h>

#include <vector>
#include <map>

namespace gfx {

class Canvas {
public:
    Canvas();
    ~Canvas();

    void clear();
    void present();

    void drawLine(
        const Point& p0, const Point& p1, const Color& c = Color::Magenta);
    void drawMultiLine(const Point& base, const std::vector<Point>& line);

    void drawRectangle(
        const Point& position,
        const Vector& size,
        const Color& color,
        int cornerRadius = 0);
    void drawFilledRectangle(
        const Point& position,
        const Vector& size,
        const Color& color,
        int cornerRadius = 0);

    void drawText(
        assets::font fontId,
        const Point& position,
        std::string_view text,
        int scale = 1);

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::map<assets::font, BitmapFont> _fonts;
};

} // namespace gfx
