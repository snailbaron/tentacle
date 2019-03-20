#pragma once

#include "geometry.hpp"

#include <vector>

struct Tentacle {
    std::vector<float> lengths;
    std::vector<Point> positions;
};

struct MrOctopus {
    Point position;
    std::vector<Tentacle> tentacles;
};

struct Core {
    void update(double delta);

    MrOctopus mrOctopus;
};
