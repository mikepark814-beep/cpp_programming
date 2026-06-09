#ifndef TETRIS_ASSIGNMENT_005_IINPUT_HPP
#define TETRIS_ASSIGNMENT_005_IINPUT_HPP

#include "GameAction.hpp"

#include <optional>

class IInput {
public:
    virtual ~IInput() = default;
    // Called before pollAction() with the game-step tick about to be processed.
    virtual void advanceTick(int) {}
    virtual std::optional<GameAction> pollAction() = 0;
};

#endif
