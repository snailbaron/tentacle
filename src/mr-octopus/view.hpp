#pragma once

#include "canvas.hpp"
#include "core.hpp"
#include "widgets.hpp"

#include <memory>

class View {
public:
    View(const Core& core);

    template <class T>
    T& addWidget()
    {
        static_assert(std::is_base_of<Widget, T>());
        _widgets.push_back(std::make_unique<T>());
        return *static_cast<T*>(_widgets.back().get());
    }

    void present();

private:
    const Core& _core;
    Canvas _canvas;
    std::vector<std::unique_ptr<Widget>> _widgets;
};
