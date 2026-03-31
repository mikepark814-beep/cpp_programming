#include "tools.h"

std::string normalize_newlines(std::string_view text) {
    std::string result;

    for (std::size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '\r') {
            if (i + 1 < text.size() && text[i + 1] == '\n') {
                result.push_back('\n');
                ++i;
            } else {
                result.push_back('\n');
            }
        } else {
            result.push_back(text[i]);
        }
    }

    return result;
}

std::string visualize_invisible(std::string_view text) {
    std::string result;

    for (char ch : text) {
        switch (ch) {
            case ' ':
                result += "[SP]";
                break;
            case '\t':
                result += "[TAB]";
                break;
            case '\n':
                result += "[LF]";
                break;
            case '\r':
                result += "[CR]";
                break;
            default:
                result.push_back(ch);
                break;
        }
    }

    return result;
}