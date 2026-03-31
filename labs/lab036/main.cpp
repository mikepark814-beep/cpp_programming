#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int score;
};

int main() {
    int n;
    std::cin >> n;

    std::vector<Student> students(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> students[i].name >> students[i].score;
    }

    std::vector<Student> qualified;
    int index = 0;

    // while 문으로 students를 검사하며 90점 이상인 학생만 qualified에 넣기
    while (index < n) {
        if (students[index].score >= 90) {
            qualified.push_back(students[index]);
        }
        ++index;
    }

    // 점수 내림차순, 이름 오름차순 정렬
    std::sort(qualified.begin(), qualified.end(),
        [](const Student& a, const Student& b) {
            if (a.score != b.score) {
                return a.score > b.score;
            }
            return a.name < b.name;
        }
    );

    // 출력
    if (qualified.empty()) {
        std::cout << "None\n";
    } else {
        int limit = qualified.size() < 3 ? qualified.size() : 3;
        for (int i = 0; i < limit; ++i) {
            std::cout << qualified[i].name << '\n';
        }
    }

    return 0;
}