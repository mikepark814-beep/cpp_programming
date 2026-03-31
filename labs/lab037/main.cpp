#include <iostream>
#include <map>
#include <string>

int main() {
    int n;
    std::cin >> n;

    std::map<std::string, int> counts;

    // 단어 n개 입력받아 개수 세기
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        ++counts[word];
    }

    // map 순회하며 출력
    for (const auto& pair : counts) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }

    return 0;
}