#include "normalize.h"
#include <cctype>
#include <algorithm>

std::string normalize(const std::string& input) {
    std::string s = input;

    // 1) trim
    auto start = s.find_first_not_of(' ');
    auto end = s.find_last_not_of(' ');
    if (start == std::string::npos) return "";
    s = s.substr(start, end - start + 1);

    // 2) 구두점 제거
    std::erase_if(s, [](unsigned char c){ return std::ispunct(c); });

    // 3) 소문자 변환
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return std::tolower(c); });

    return s;
}