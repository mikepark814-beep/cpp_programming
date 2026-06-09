#include "ConfigLoader.hpp"
#include "Grid.hpp"
#include "ScoreRepository.hpp"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

void print_scores(const std::vector<int>& v) {
    std::cout << "scores=";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i != 0) {
            std::cout << ',';
        }
        std::cout << v[i];
    }
    std::cout << '\n';
}

std::filesystem::path tmp_path(const std::string& label) {
    return std::filesystem::temp_directory_path() / ("tetris_v2_006_int_" + label + ".txt");
}

void remove_if_exists(const std::filesystem::path& path) {
    std::error_code ignored;
    std::filesystem::remove(path, ignored);
}

} // namespace

int main() {
    std::ios_base::sync_with_stdio(false);
    std::istream& input = std::cin;

    Grid<char, 10, 10> grid;
    grid.fill('.');

    std::filesystem::path score_path = tmp_path("default_score");
    remove_if_exists(score_path);

    std::filesystem::path cfg_path = tmp_path("default_cfg");
    remove_if_exists(cfg_path);
    std::filesystem::path score_blocker_path;

    auto repo = [&]() { return ScoreRepository(score_path.string()); };

    std::string token;
    while (input >> token) {
        if (token == "gfill") {
            char c = '.';
            input >> c;
            grid.fill(c);
        } else if (token == "gset") {
            int x = 0;
            int y = 0;
            char c = '.';
            input >> x >> y >> c;
            grid.at(x, y) = c;
        } else if (token == "gget") {
            int x = 0;
            int y = 0;
            input >> x >> y;
            std::cout << "get(" << x << "," << y << ")="
                      << grid.at(x, y) << '\n';
        } else if (token == "gprint") {
            std::cout << "grid=" << grid.width() << "x" << grid.height() << '\n';
            for (std::size_t y = 0; y < grid.height(); ++y) {
                for (std::size_t x = 0; x < grid.width(); ++x) {
                    std::cout << grid.at(x, y);
                }
                std::cout << '\n';
            }
        } else if (token == "gbounds") {
            int x = 0;
            int y = 0;
            input >> x >> y;
            try {
                grid.at(x, y) = 'X';
                std::cout << "set(" << x << "," << y << ")=ok\n";
            } catch (const std::out_of_range&) {
                std::cout << "set(" << x << "," << y << ")=oob\n";
            }
        } else if (token == "gconst_bounds") {
            int x = 0;
            int y = 0;
            input >> x >> y;
            const Grid<char, 10, 10>& view = grid;
            try {
                (void)view.at(x, y);
                std::cout << "const_get(" << x << "," << y << ")=ok\n";
            } catch (const std::out_of_range&) {
                std::cout << "const_get(" << x << "," << y << ")=oob\n";
            }
        } else if (token == "spath") {
            std::string label;
            input >> label;
            if (!score_blocker_path.empty()) {
                remove_if_exists(score_blocker_path);
                score_blocker_path.clear();
            }
            score_path = tmp_path("score_" + label);
            remove_if_exists(score_path);
        } else if (token == "spath_blocked") {
            if (!score_blocker_path.empty()) {
                remove_if_exists(score_blocker_path);
            }
            score_blocker_path = tmp_path("score_blocked_parent");
            std::filesystem::remove_all(score_blocker_path);
            {
                std::ofstream blocker(score_blocker_path);
                blocker << "not a directory\n";
            }
            score_path = score_blocker_path / "scores.txt";
        } else if (token == "sclear") {
            remove_if_exists(score_path);
        } else if (token == "sshow") {
            std::ifstream in(score_path);
            std::cout << "file=";
            int v = 0;
            bool first = true;
            while (in >> v) {
                if (!first) std::cout << ',';
                std::cout << v;
                first = false;
            }
            std::cout << '\n';
        } else if (token == "ssave_n") {
            int n = 0;
            input >> n;
            std::vector<int> v;
            v.reserve(static_cast<std::size_t>(n));
            for (int i = 0; i < n; ++i) {
                int s = 0;
                input >> s;
                v.push_back(s);
            }
            try {
                repo().save(v);
            } catch (const ScoreError& e) {
                std::cout << "save_error=" << e.what() << '\n';
            }
        } else if (token == "swrite_raw") {
            int n = 0;
            input >> n;
            std::ofstream out(score_path);
            for (int i = 0; i < n; ++i) {
                std::string item;
                input >> item;
                out << item << '\n';
            }
        } else if (token == "sadd") {
            int score = 0;
            std::size_t limit = 0;
            input >> score >> limit;
            try {
                repo().addScore(score, limit);
            } catch (const ScoreError& e) {
                std::cout << "save_error=" << e.what() << '\n';
            }
        } else if (token == "sload") {
            try {
                print_scores(repo().load());
            } catch (const ScoreError& e) {
                std::cout << "load_error=" << e.what() << '\n';
            }
        } else if (token == "cpath") {
            std::string label;
            input >> label;
            cfg_path = tmp_path("cfg_" + label);
            remove_if_exists(cfg_path);
        } else if (token == "cclear") {
            remove_if_exists(cfg_path);
        } else if (token == "cwrite_n") {
            int n = 0;
            input >> n;
            std::ofstream out(cfg_path);
            for (int i = 0; i < n; ++i) {
                std::string line;
                input >> line;
                out << line << '\n';
            }
        } else if (token == "cload") {
            try {
                const GameConfig cfg = load_config_file(cfg_path.string());
                std::cout << "cfg w=" << cfg.board_width
                          << " h=" << cfg.board_height
                          << " hz=" << cfg.tick_rate
                          << " font=" << cfg.font_path << '\n';
            } catch (const ConfigError& e) {
                std::cout << "cfg_error=" << e.what() << '\n';
            }
        } else if (token == "end") {
            break;
        } else {
            std::cerr << "unknown command: " << token << '\n';
            return 2;
        }
    }
    remove_if_exists(score_path);
    if (!score_blocker_path.empty()) {
        remove_if_exists(score_blocker_path);
    }
    remove_if_exists(cfg_path);
    return 0;
}
