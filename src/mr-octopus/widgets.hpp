#pragma once

#include <gfx/canvas.hpp>

#include <string>

class Widget {
public:
    virtual ~Widget() {}

    virtual void draw(gfx::Canvas& canvas) const = 0;
};

class Button : public Widget {
public:
    Button& position(const gfx::Point& position);
    Button& size(const gfx::Vector& size);
    Button& text(std::string text);

    void draw(gfx::Canvas& canvas) const override;

private:
    static constexpr auto BorderWidth = 10;

    gfx::Point _position;
    gfx::Vector _size;
    std::string _text;
};
