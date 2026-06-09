// TODO: 다음 함수들을 정의하세요. 인터페이스/규칙/힌트 참조.
//
//   ReplayWriter::ReplayWriter(std::string path, ReplayHeader header)
//   ReplayWriter::~ReplayWriter()
//   ReplayWriter::append(const ReplayEvent& ev)
//   ReplayWriter::finalize(int final_score, int final_tick)
//   ReplayWriter::finalized() const noexcept
//
//   ReplayReader::ReplayReader(std::string path)
//   ReplayReader::header() const noexcept
//   ReplayReader::complete() const noexcept
//   ReplayReader::checksum_ok() const noexcept
//   ReplayReader::final_score() const noexcept
//   ReplayReader::final_tick() const noexcept
//   ReplayReader::events_strict() const
//   ReplayReader::events_partial() const
//
// 출력 헬퍼 (replay_io.h) 는 채점 드라이버 main.cpp 가 호출합니다.
// 학생 코드에서 std::print / std::cout 등을 직접 호출할 필요가 없습니다.

#include "Replay.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace fs = std::filesystem;

// ===== 내부 헬퍼 =====

namespace {

unsigned byte_sum(const std::string& s) {
    unsigned sum = 0;
    for (unsigned char c : s) sum += c;
    return sum;
}

std::vector<std::string> split_spaces(const std::string& s) {
    std::vector<std::string> tokens;
    std::istringstream ss(s);
    std::string tok;
    while (ss >> tok) tokens.push_back(tok);
    return tokens;
}

std::pair<std::string, std::string> parse_kv(const std::string& tok) {
    auto pos = tok.find('=');
    if (pos == std::string::npos) return {tok, ""};
    return {tok.substr(0, pos), tok.substr(pos + 1)};
}

} // namespace

// ===== ReplayWriter =====

ReplayWriter::ReplayWriter(std::string path, ReplayHeader header)
    : path_(std::move(path)), header_(std::move(header))
{
    out_.open(path_, std::ios::out | std::ios::trunc);
    if (!out_.is_open())
        throw ReplayIoError("cannot open file for writing: " + path_);

    out_ << "TETRIS_REPLAY v" << header_.version << "\n";
    out_ << "match_id=" << header_.match_id
         << " seed=" << header_.seed
         << " player=" << header_.player
         << " mode=" << header_.mode
         << " tick_rate=" << header_.tick_rate
         << "\n";
    out_.flush();
}

ReplayWriter::~ReplayWriter() {
    if (!finalized_) {
        try { finalize(0, 0); } catch (...) {}
    }
}

void ReplayWriter::append(const ReplayEvent& ev) {
    if (finalized_)
        throw ReplayError("append after finalize");
    if (ev.tick < last_tick_)
        throw ReplayError("tick decreased");
    last_tick_ = ev.tick;

    std::string line = std::format("EVENT tick={} action={}", ev.tick, ev.action);
    for (const auto& [k, v] : ev.extras)
        line += " " + k + "=" + v;
    line += "\n";

    running_sum_ += byte_sum(line);
    out_ << line;
    out_.flush();
}

void ReplayWriter::finalize(int final_score, int final_tick) {
    if (finalized_)
        throw ReplayError("double finalize");
    out_ << std::format("END score={} ticks={} checksum=0X{:04X}\n",
                        final_score, final_tick, running_sum_);
    out_.flush();
    finalized_ = true;
}

bool ReplayWriter::finalized() const noexcept { return finalized_; }

// ===== ReplayReader =====

ReplayReader::ReplayReader(std::string path) : path_(std::move(path)) {
    if (!fs::exists(path_))
        throw ReplayIoError("file not found: " + path_);
    std::ifstream in(path_);
    if (!in.is_open())
        throw ReplayIoError("cannot open file: " + path_);

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) lines.push_back(line);

    if (lines.empty())
        throw ReplayFormatError("empty file");

    // Line 1: TETRIS_REPLAY v1
    {
        auto tokens = split_spaces(lines[0]);
        if (tokens.size() < 2 || tokens[0] != "TETRIS_REPLAY")
            throw ReplayFormatError("bad magic: " + lines[0]);
        const auto& ver = tokens[1];
        if (ver.size() < 2 || ver[0] != 'v')
            throw ReplayVersionError("bad version: " + ver);
        try {
            int v = std::stoi(ver.substr(1));
            if (v != 1) throw ReplayVersionError("unsupported version: " + ver);
            header_.version = v;
        } catch (const ReplayVersionError&) {
            throw;
        } catch (...) {
            throw ReplayVersionError("bad version: " + ver);
        }
    }

    if (lines.size() < 2)
        throw ReplayFormatError("missing header line");

    // Line 2: header key=value pairs
    {
        auto tokens = split_spaces(lines[1]);
        bool has_match_id = false, has_seed = false, has_player = false;
        bool has_mode = false, has_tick_rate = false;

        for (const auto& tok : tokens) {
            auto [key, val] = parse_kv(tok);
            if (val.empty())
                throw ReplayFormatError("empty value for key: " + key);

            if (key == "match_id") {
                if (has_match_id) throw ReplayFormatError("duplicate key: match_id");
                header_.match_id = std::stoi(val);
                has_match_id = true;
            } else if (key == "seed") {
                if (has_seed) throw ReplayFormatError("duplicate key: seed");
                header_.seed = std::stoi(val);
                has_seed = true;
            } else if (key == "player") {
                if (has_player) throw ReplayFormatError("duplicate key: player");
                header_.player = val;
                has_player = true;
            } else if (key == "mode") {
                if (has_mode) throw ReplayFormatError("duplicate key: mode");
                header_.mode = val;
                has_mode = true;
            } else if (key == "tick_rate") {
                if (has_tick_rate) throw ReplayFormatError("duplicate key: tick_rate");
                header_.tick_rate = std::stoi(val);
                has_tick_rate = true;
            }
            // unknown keys are silently ignored
        }

        if (!has_match_id) throw ReplayFormatError("missing required field: match_id");
        if (!has_seed)     throw ReplayFormatError("missing required field: seed");
        if (!has_player)   throw ReplayFormatError("missing required field: player");
    }

    // Remaining lines: EVENT or END
    unsigned computed_sum = 0;
    bool found_end = false;

    for (std::size_t i = 2; i < lines.size(); ++i) {
        const auto& l = lines[i];
        if (l.empty()) continue;

        if (l.rfind("EVENT ", 0) == 0) {
            if (found_end) {
                end_followed_by_garbage_ = true;
                continue;
            }
            computed_sum += byte_sum(l + "\n");

            auto tokens = split_spaces(l);
            ReplayEvent ev;
            for (std::size_t j = 1; j < tokens.size(); ++j) {
                auto [key, val] = parse_kv(tokens[j]);
                if (key == "tick")        ev.tick = std::stoi(val);
                else if (key == "action") ev.action = val;
                else                      ev.extras.emplace_back(key, val);
            }
            events_.push_back(std::move(ev));
        } else if (l.rfind("END ", 0) == 0) {
            found_end = true;
            auto tokens = split_spaces(l);
            unsigned stored_checksum = 0;
            for (std::size_t j = 1; j < tokens.size(); ++j) {
                auto [key, val] = parse_kv(tokens[j]);
                if (key == "score")         final_score_ = std::stoi(val);
                else if (key == "ticks")    final_tick_  = std::stoi(val);
                else if (key == "checksum") {
                    if (val.size() >= 2 && val[0] == '0' && val[1] == 'X')
                        stored_checksum = static_cast<unsigned>(
                            std::stoul(val.substr(2), nullptr, 16));
                }
            }
            complete_ = true;
            checksum_ok_ = (stored_checksum == computed_sum);
        }
    }
}

const ReplayHeader& ReplayReader::header()      const noexcept { return header_; }
bool                ReplayReader::complete()    const noexcept { return complete_; }
bool                ReplayReader::checksum_ok() const noexcept { return checksum_ok_; }
int                 ReplayReader::final_score() const noexcept { return final_score_; }
int                 ReplayReader::final_tick()  const noexcept { return final_tick_; }

std::vector<ReplayEvent> ReplayReader::events_strict() const {
    if (!complete_)
        throw ReplayFormatError("incomplete replay: missing END line");
    if (!checksum_ok_)
        throw ReplayFormatError("checksum mismatch");
    if (end_followed_by_garbage_)
        throw ReplayFormatError("events found after END line");
    return events_;
}

std::vector<ReplayEvent> ReplayReader::events_partial() const {
    return events_;
}
