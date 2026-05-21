#include "tetris.h"
#include <sstream>

void init_game(GameState& state) {
    state.board.assign(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, '.'));
    state.block_x = 4;
    state.block_y = 0;
    state.current_block = {{1, 1, 1, 1}};
    state.running = true;
}

std::string board_to_string(const GameState& state) {
    auto rendered = state.board;

    for (int sy = 0; sy < (int)state.current_block.size(); ++sy) {
        for (int sx = 0; sx < (int)state.current_block[sy].size(); ++sx) {
            if (state.current_block[sy][sx] == 0) continue;
            int by = state.block_y + sy;
            int bx = state.block_x + sx;
            if (by >= 0 && by < BOARD_HEIGHT && bx >= 0 && bx < BOARD_WIDTH) {
                rendered[by][bx] = '#';
            }
        }
    }

    std::ostringstream out;
    out << "+----------+\n";
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        out << '|';
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            out << rendered[y][x];
        }
        out << "|\n";
    }
    out << "+----------+\n";
    return out.str();
}
