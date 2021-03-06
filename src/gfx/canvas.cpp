#include <gfx/canvas.hpp>

#include <SDL2/SDL2_gfxPrimitives.h>

#include <cassert>

namespace gfx {

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

    for (size_t i = 0; i < assets::fontsCount(); i++) {
        auto font = static_cast<assets::font>(i);
        _fonts.insert({font, BitmapFont(_renderer, assets::path(font))});
    }
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

void Canvas::drawLine(
    const Point& p0, const Point& p1, const Color& c)
{
    thickLineRGBA(_renderer, p0.x, p0.y, p1.x, p1.y, 3, c.r, c.g, c.b, c.a);
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
    int cornerRadius)
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
    int cornerRadius)
{
    auto corner = position - size / 2;
    roundedBoxRGBA(
        _renderer,
        corner.x, corner.y,
        corner.x + size.x, corner.y + size.y,
        cornerRadius,
        color.r, color.g, color.b, color.a);
}

void Canvas::drawText(
    assets::font fontId,
    const Point& position,
    std::string_view text,
    int scale)
{
    assert(scale >= 1);

    auto& font = _fonts.at(fontId);
    auto x = position.x - static_cast<int>(
        font.charWidth() * text.length() * scale / 2);
    auto y = position.y - static_cast<int>(font.charHeight() * scale / 2);
    SDL_Rect dstRect {x, y, 0, 0};

    auto fontTexture = font.texture();
    for (auto symbol : text) {
        auto srcRect = font[symbol];
        dstRect.w = srcRect.w * scale;
        dstRect.h = srcRect.h * scale;

        SDL_RenderCopy(_renderer, fontTexture, &srcRect, &dstRect);
        dstRect.x += dstRect.w + scale;
    }
}

} // namespace gfx
