#include "view.hpp"

View::View(const Core& core)
    : _core(core)
{ }

void View::present()
{
    _canvas.clear();

    for (const auto& tentacle : _core.mrOctopus.tentacles) {
        for (size_t i = 0; i + 1 < tentacle.positions.size(); i++) {
            const auto& t0 = tentacle.positions.at(i);
            const auto& t1 = tentacle.positions.at(i + 1);

            auto x0 = static_cast<int>(t0.x);
            auto y0 = static_cast<int>(t0.y);
            auto x1 = static_cast<int>(t1.x);
            auto y1 = static_cast<int>(t1.y);

            _canvas.drawLine({x0, y0}, {x1, y1});
        }
    }

    for (auto& widget : _widgets) {
        widget->draw(_canvas);
    }

    _canvas.present();
}
