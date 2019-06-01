#pragma once

#include <cstdint>

namespace gfx {

struct Color {
    // Pink colors
    static const Color Pink;
    static const Color LightPink;
    static const Color HotPink;
    static const Color DeepPink;
    static const Color PaleVioletRed;
    static const Color MediumVioletRed;

    // Red colors
    static const Color LightSalmon;
    static const Color Salmon;
    static const Color DarkSalmon;
    static const Color LightCoral;
    static const Color IndianRed;
    static const Color Crimson;
    static const Color Firebrick;
    static const Color DarkRed;
    static const Color Red;

    // Orange colors
    static const Color OrangeRed;
    static const Color Tomato;
    static const Color Coral;
    static const Color DarkOrange;
    static const Color Orange;

    // Yellow colors
    static const Color Yellow;
    static const Color LightYellow;
    static const Color LemonChiffon;
    static const Color LightGoldenrodYellow;
    static const Color PapayaWhip;
    static const Color Moccasin;
    static const Color PeachPuff;
    static const Color PaleGoldenrod;
    static const Color Khaki;
    static const Color DarkKhaki;
    static const Color Gold;

    // Brown colors
    static const Color Cornsilk;
    static const Color BlanchedAlmond;
    static const Color Bisque;
    static const Color NavajoWhite;
    static const Color Wheat;
    static const Color Burlywood;
    static const Color Tan;
    static const Color RosyBrown;
    static const Color SandyBrown;
    static const Color Goldenrod;
    static const Color DarkGoldenrod;
    static const Color Peru;
    static const Color Chocolate;
    static const Color SaddleBrown;
    static const Color Sienna;
    static const Color Brown;
    static const Color Maroon;

    // Green colors
    static const Color DarkOliveGreen;
    static const Color Olive;
    static const Color OliveDrab;
    static const Color YellowGreen;
    static const Color LimeGreen;
    static const Color Lime;
    static const Color LawnGreen;
    static const Color Chartreuse;
    static const Color GreenYellow;
    static const Color SpringGreen;
    static const Color MediumSpringGreen;
    static const Color LightGreen;
    static const Color PaleGreen;
    static const Color DarkSeaGreen;
    static const Color MediumAquamarine;
    static const Color MediumSeaGreen;
    static const Color SeaGreen;
    static const Color ForestGreen;
    static const Color Green;
    static const Color DarkGreen;

    // Cyan colors
    static const Color Aqua;
    static const Color Cyan;
    static const Color LightCyan;
    static const Color PaleTurquoise;
    static const Color Aquamarine;
    static const Color Turquoise;
    static const Color MediumTurquoise;
    static const Color DarkTurquoise;
    static const Color LightSeaGreen;
    static const Color CadetBlue;
    static const Color DarkCyan;
    static const Color Teal;

    // Blue colors
    static const Color LightSteelBlue;
    static const Color PowderBlue;
    static const Color LightBlue;
    static const Color SkyBlue;
    static const Color LightSkyBlue;
    static const Color DeepSkyBlue;
    static const Color DodgerBlue;
    static const Color CornflowerBlue;
    static const Color SteelBlue;
    static const Color RoyalBlue;
    static const Color Blue;
    static const Color MediumBlue;
    static const Color DarkBlue;
    static const Color Navy;
    static const Color MidnightBlue;

    // Purple, violet, and magenta colors
    static const Color Lavender;
    static const Color Thistle;
    static const Color Plum;
    static const Color Violet;
    static const Color Orchid;
    static const Color Fuchsia;
    static const Color Magenta;
    static const Color MediumOrchid;
    static const Color MediumPurple;
    static const Color BlueViolet;
    static const Color DarkViolet;
    static const Color DarkOrchid;
    static const Color DarkMagenta;
    static const Color Purple;
    static const Color Indigo;
    static const Color DarkSlateBlue;
    static const Color SlateBlue;
    static const Color MediumSlateBlue;

    // White colors
    static const Color White;
    static const Color Snow;
    static const Color Honeydew;
    static const Color MintCream;
    static const Color Azure;
    static const Color AliceBlue;
    static const Color GhostWhite;
    static const Color WhiteSmoke;
    static const Color Seashell;
    static const Color Beige;
    static const Color OldLace;
    static const Color FloralWhite;
    static const Color Ivory;
    static const Color AntiqueWhite;
    static const Color Linen;
    static const Color LavenderBlush;
    static const Color MistyRose;

    // Gray and black colors
    static const Color Gainsboro;
    static const Color LightGray;
    static const Color Silver;
    static const Color DarkGray;
    static const Color Gray;
    static const Color DimGray;
    static const Color LightSlateGray;
    static const Color SlateGray;
    static const Color DarkSlateGray;
    static const Color Black;

    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r), g(g), b(b), a(a)
    { }

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

} // namespace gfx
