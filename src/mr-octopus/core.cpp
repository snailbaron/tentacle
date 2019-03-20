#include "core.hpp"

void Core::update(double delta)
{
    constexpr static auto TENTACLE_SHRINK_SPEED = 0.001;

    for (auto& tentacle : mrOctopus.tentacles) {
        for (size_t i = 0; i + 1 < tentacle.positions.size(); ++i) {
            const auto& maxLength = tentacle.lengths.at(i);
            const auto& prev = tentacle.positions.at(i);
            auto& current = tentacle.positions[i+1];
            auto vectorToPrev = prev - current;
            auto currentLength = length(vectorToPrev);
            auto extraLength = std::max(Scalar{0}, currentLength - maxLength);
            if (extraLength > 0) {
                current += normalized(vectorToPrev) * extraLength * delta *
                    TENTACLE_SHRINK_SPEED;
            }
        }
    }
}
