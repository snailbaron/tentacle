#include "widgets.hpp"

Button& Button::position(const gfx::Point& position)
{
    _position = position;
    return *this;
}

Button& Button::size(const gfx::Vector& size)
{
    _size = size;
    return *this;
}

Button& Button::text(std::string text)
{
    _text = std::move(text);
    return *this;
}

void Button::draw(gfx::Canvas& canvas) const
{
    canvas.drawFilledRectangle(_position, _size, gfx::Color::Black, 5);

    auto innerSize = gfx::Vector{_size.x - BorderWidth, _size.y - BorderWidth};
    canvas.drawFilledRectangle(_position, innerSize, gfx::Color::Yellow, 5);

    canvas.drawText(assets::font::octo, _position, "button", 3);
}
