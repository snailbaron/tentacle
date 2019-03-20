#include "canvas.hpp"

#include <SDL2_gfxPrimitives.h>

#include <cassert>

Canvas::Canvas()
{
    _window = SDL_CreateWindow(
        "Mr. Octopus",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_FULLSCREEN_DESKTOP);
    assert(_window);

    _renderer = SDL_CreateRenderer(
        _window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    assert(_renderer);
}

Canvas::~Canvas()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void Canvas::clear()
{
    SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);
    SDL_RenderClear(_renderer);
}

void Canvas::present()
{
    SDL_RenderPresent(_renderer);
}

void Canvas::drawMultiLine(const Point& base, const std::vector<Point>& line)
{
    for (size_t i = 0; i + 1 < line.size(); ++i) {
        thickLineRGBA(
            _renderer,
            base.x + line[i].x,
            base.y + line[i].y,
            base.x + line[i+1].x,
            base.y + line[i+1].y,
            3,
            100, 50, 100, 255);
    }

    for (const auto& point : line) {
        filledCircleRGBA(
            _renderer,
            base.x + point.x,
            base.y + point.y,
            4,
            100, 50, 100, 255);
    }
}

void Canvas::drawRectangle(
    const Point& position,
    const Vector& size,
    const Color& color,
    Scalar cornerRadius)
{
    auto corner = position - size / 2;
    roundedRectangleRGBA(
        _renderer,
        corner.x, corner.y,
        corner.x + size.x, corner.y + size.y,
        cornerRadius,
        color.r, color.g, color.b, color.a);
}

void Canvas::drawFilledRectangle(
    const Point& position,
    const Vector& size,
    const Color& color,
    Scalar cornerRadius)
{
    auto corner = position - size / 2;
    roundedBoxRGBA(
        _renderer,
        corner.x, corner.y,
        corner.x + size.x, corner.y + size.y,
        cornerRadius,
        color.r, color.g, color.b, color.a);
}

void Canvas::drawText(const BitmapFont& font, std::string_view text)
{
    //SDL_RenderCopy(_renderer, texture, srcrect, dstrect);
}
