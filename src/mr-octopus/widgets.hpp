#pragma once

#include "canvas.hpp"
#include "geometry.hpp"

#include <string>

class Widget {
public:
    virtual ~Widget() {}

    virtual void draw(Canvas& canvas) const = 0;
};

class Button : public Widget {
public:
    Button& position(const Point& position);
    Button& size(const Vector& size);
    Button& text(std::string text);

    void draw(Canvas& canvas) const override;

private:
    static constexpr auto BorderWidth = Scalar{10};

    Point _position;
    Vector _size;
    std::string _text;
};
