#include "tetris.h"

bool ActivePiece::operator==(const ActivePiece& other) const {
    // TODO: position 비교 + piece.cells({0,0}) 비교
    (void)other;
    return false;
}

// 익명 namespace 에 helpers 를 두세요:
//   bool can_place(const Board& board, const Piece& piece, Position origin)
//     → piece.cells(origin) 각 좌표에 대해 inBounds + cell('.') 검사
//   void lock_piece(Board& board, const Piece& piece, Position origin)
//     → piece.cells(origin) 각 좌표를 '#' 으로 기록
//   bool spawn_piece(GameState& state)
//     → active 리셋 + can_place 로 top-out 검사 후 반환

bool move_piece(GameState& state, int dx, int dy) {
    // Position next{state.active.position.x + dx, state.active.position.y + dy};
    // if (can_place(state.board, state.active.piece, next)) { ... }
    (void)dx; (void)dy;
    return false;
}

void hard_drop(GameState& state) {
    // TODO: while (move_piece(state, 0, 1)) {}
    //       lock_piece(state.board, state.active.piece, state.active.position);
    //       state.running = spawn_piece(state);
}

void update_game(GameState& state) {
    if (!state.running) return;
    ++state.tick;
    // TODO: tick % fall_interval == 0 && !move_piece(0, 1) → lock + spawn
}

void handle_game_action(GameState& state, GameAction action) {
    if (!state.running && action != GameAction::Quit) return;
    switch (action) {
        case GameAction::Left:  break;  // TODO
        case GameAction::Right: break;  // TODO
        case GameAction::Down:  break;  // TODO
        case GameAction::Drop:  break;  // TODO
        case GameAction::Quit:  break;  // TODO
        case GameAction::None:  break;
    }
    (void)state;
}

GameAction parse_action(const std::string& token) {
    // TODO: "LEFT"/"RIGHT"/"DOWN"/"DROP"/"QUIT" → enum, 그 외 None
    (void)token;
    return GameAction::None;
}

std::string action_to_string(GameAction action) {
    // TODO: enum → 문자열 round-trip
    (void)action;
    return "NONE";
}
