#include "board_util.h"
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

static std::vector<std::vector<int>> board;

// 힌트: is_full 헬퍼 람다를 여러 함수에서 재사용할 수 있습니다.
static auto is_full = [](const std::vector<int>& row) {
    return std::ranges::all_of(row, [](int x) { return x == 1; });
};

void init_board() {
    board = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0},
        {1, 1, 1, 1, 1}
    };
}

const std::vector<std::vector<int>>& get_board() {
    return board;
}

int count_full_lines() {
    // TODO: 모든 칸이 1인 행의 수를 반환하세요.
    return (int)std::ranges::count_if(board, is_full);
}

void remove_full_lines() {
    // TODO: 완성된 행을 제거하고, 제거된 수만큼 빈 행을 위에 삽입하세요.
    int cols = board.empty() ? 0 : (int)board[0].size();
    size_t removed = std::erase_if(board, is_full);
    
    if (removed > 0) {
        board.insert(board.begin(), removed, std::vector<int>(cols, 0));
    }
}

std::vector<int> get_heights() {
    // TODO: 각 열에서 블록이 쌓인 높이를 반환하세요.
    int cols = board.empty() ? 0 : (int)board[0].size();
    int rows = (int)board.size();

    return std::views::iota(0, cols) 
        | std::views::transform([&](int c) {
            for (int r = 0; r < rows; ++r) {
                if (board[r][c] == 1) return rows - r;
            }
            return 0;
        })
        | std::ranges::to<std::vector>();
}

int count_empty() {
    // TODO: 보드 전체에서 빈 칸(0)의 수를 반환하세요.
    auto row_empty_counts = board | std::views::transform([](const auto& row) {
        return (int)std::ranges::count(row, 0);
    });

    // C++23 fold_left를 사용하거나 std::accumulate 사용
    return std::accumulate(row_empty_counts.begin(), row_empty_counts.end(), 0);
}
