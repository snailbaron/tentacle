#include "core.hpp"
#include "view.hpp"
#include "widgets.hpp"

#include <gfx/canvas.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <cassert>
#include <vector>

constexpr auto GAME_FPS = 60;

constexpr auto SECONDS_PER_FRAME = 1.0 / GAME_FPS;

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    Core core;
    View view(core);

    view.addWidget<Button>()
        .position({800, 50})
        .size({200, 50})
        .text("exit");

    core.mrOctopus.position = {800, 200};
    core.mrOctopus.tentacles.resize(2);
    core.mrOctopus.tentacles[0].lengths = {20, 50};
    core.mrOctopus.tentacles[0].positions = {
        {5, 0}, {20, 30}, {40, 100}};
    core.mrOctopus.tentacles[1].lengths = {30, 60};
    core.mrOctopus.tentacles[1].positions = {
        {-5, 0}, {-30, 50}, {-60, 200}};

    bool done = false;
    auto prevTicks = SDL_GetTicks();
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        done = true;
                        break;
                    }
                    break;
            }
        }

        if (done) {
            break;
        }

        auto currentTicks = SDL_GetTicks();
        auto framesPassed = static_cast<int>(
            currentTicks - prevTicks / SECONDS_PER_FRAME / 1000);
        if (framesPassed == 0) {
            continue;
        }
        prevTicks = currentTicks;

        for (auto i = framesPassed; i > 0; --i) {
            core.update(SECONDS_PER_FRAME);
        }
        view.present();
    }

    IMG_Quit();
    SDL_Quit();
}
