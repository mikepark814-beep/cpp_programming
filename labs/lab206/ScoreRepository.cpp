#include "ScoreRepository.hpp"

#include <utility>
#include <filesystem>
#include <fstream>
#include <algorithm>

ScoreError::ScoreError(const std::string& message) : std::runtime_error(message) {}
ScoreRepository::ScoreRepository(std::string path) : path_(std::move(path)) {}
std::vector<int> ScoreRepository::load() const {
    // TODO: Return an empty list for a missing file; throw ScoreError for unreadable or corrupt content.
    if (!std::filesystem::exists(path_)) {
        return {};
    }

    std::ifstream file(path_);
    if (!file.is_open()) {
        throw ScoreError("Cannot open file");
    }

    std::vector<int> scores;
    std::string line;
    while (std::getline(file, line)) {
        try {
            scores.push_back(std::stoi(line));
        }

        catch (const std::exception&) {
            throw ScoreError("Corrupt content");
        }
    }
    
    return scores;
}
void ScoreRepository::save(const std::vector<int>& scores) const {
    // TODO: Overwrite path_ with one score per line.
    std::ofstream file(path_);
    for (int score : scores) {
        file << score << "\n";
    }
}
void ScoreRepository::addScore(int score, std::size_t limit) const {
    // TODO: Load, insert score, sort descending, keep at most limit values, then save.
    auto scores = load();

    scores.push_back(score);

    std::sort(scores.begin(), scores.end(), std::greater<int>());

    if (scores.size() > limit) {
        scores.resize(limit);
    }

    save(scores);
}
