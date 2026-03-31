#include <cctype>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int countCharacter(const std::string& str, char ch) {
    // TODO: str에서 문자 ch가 몇 번 등장하는지 세어 반환하세요.
    int count = 0;
    for(char c : str) {
        if(c == ch) {
            count++;
        }
    }
    return count;
}

void toUpperCase(std::string& str) {
    // TODO: str의 모든 문자를 대문자로 바꾸세요.
    for(char& c : str) {
        c = std::toupper(c);
    }
}

bool startsWith(std::string_view str, std::string_view prefix) {
    // TODO: str이 prefix로 시작하면 true, 아니면 false를 반환하세요.
    return str.substr(0 , prefix.size()) == prefix;
}

int main() {
    std::vector<std::string> words = {"hello", "world", "example"};

    char characterToCount = 'l';
    for (const auto& word : words) {
        std::cout << "Count of '" << characterToCount << "' in \"" << word << "\": "
                  << countCharacter(word, characterToCount) << '\n';
    }
    std::cout << '\n';

    for (auto& word : words) {
        toUpperCase(word);
        std::cout << "Modified string: " << word << '\n';
    }
    std::cout << '\n';

    std::string_view prefix = "EX";
    for (const auto& word : words) {
        std::cout << "Does \"" << word << "\" start with '" << prefix << "'? "
                  << (startsWith(word, prefix) ? "Yes" : "No") << '\n';
    }

    return 0;
}
