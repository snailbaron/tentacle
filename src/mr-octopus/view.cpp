#include "view.hpp"

View::View(const Core& core)
    : _core(core)
{ }

void View::present()
{
    _canvas.clear();

    for (const auto& tentacle : _core.mrOctopus.tentacles) {
        _canvas.drawMultiLine(_core.mrOctopus.position, tentacle.positions);
    }

    for (auto& widget : _widgets) {
        widget->draw(_canvas);
    }

    _canvas.present();
}
