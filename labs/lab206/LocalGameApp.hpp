#ifndef TETRIS_ASSIGNMENT_005_LOCAL_GAME_APP_HPP
#define TETRIS_ASSIGNMENT_005_LOCAL_GAME_APP_HPP

#include "IInput.hpp"
#include "IRenderer.hpp"
#include "tetris.h"

#include <chrono>

class LocalGameApp {
public:
    LocalGameApp(GameCore core, IRenderer& renderer, IInput& input, int tick_rate_hz = 20);

    void singleTick();
    void run(int max_ticks = -1);

private:
    GameCore core_;
    IRenderer& renderer_;
    IInput& input_;
    int tick_rate_hz_ = 20;
    int tick_count_ = 1;
};

#endif
