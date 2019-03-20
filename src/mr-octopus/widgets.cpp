#include "widgets.hpp"

Button& Button::position(const Point& position)
{
    _position = position;
    return *this;
}

Button& Button::size(const Vector& size)
{
    _size = size;
    return *this;
}

Button& Button::text(std::string text)
{
    _text = std::move(text);
    return *this;
}

void Button::draw(Canvas& canvas) const
{
    canvas.drawFilledRectangle(_position, _size, Color::Black, 5);

    auto innerSize = Vector{_size.x - BorderWidth, _size.y - BorderWidth};
    canvas.drawFilledRectangle(_position, innerSize, Color::Yellow, 5);
}
