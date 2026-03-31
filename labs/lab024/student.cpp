#include "student.h"

std::array<Student, STUDENT_COUNT> init_students() {
    return {{
        {1, "Choi", 9.9},
        {2, "Park", 0.1},
        {3, "Kim", 5.0},
        {4, "Lee", 3.0},
        {5, "Moon", 9.5},
        {6, "Kang", 7.0},
        {7, "Jeon", 0.9}
    }};
}

const Student& get_last(const std::array<Student, STUDENT_COUNT>& students) {
    // TODO: return the last student in the array.
    return students[STUDENT_COUNT - 1];
    return students[0];
}

std::string compare_points(const Student& s1, const Student& s2) {
    // TODO: 점수를 비교해 의미 있는 문장을 반환하세요.
        if(s1.points > s2.points) {
            return s1.name + " has more points than " + s2.name;
        }
        else if(s1.points < s2.points) {
            return s2.name + " has more points than " + s1.name;
        }
        else {
            return s1.name + " and " + s2.name + " have the same points";
        }
    return "";
}

const Student& get_lowest_points(const std::array<Student, STUDENT_COUNT>& students) {
    // TODO: 가장 낮은 점수의 학생을 찾아 반환하세요.
    for(size_t i = 1; i < STUDENT_COUNT; ++i) {
        if(students[i].points < students[0].points) {
            return students[i];
        }
    }
    return students[0];
}

const Student& get_highest_points(const std::array<Student, STUDENT_COUNT>& students) {
    // TODO: 가장 높은 점수의 학생을 찾아 반환하세요.
    for(size_t i = 1; i < STUDENT_COUNT; ++i) {
        if(students[i].points > students[0].points) {
            return students[i];
        }
    }
    return students[0];
}

void my_sort(std::array<Student, STUDENT_COUNT>& students) {
    // TODO: points 오름차순으로 정렬하세요.
    for(size_t i = 0; i < STUDENT_COUNT - 1; ++i) {
        for(size_t j = 0; j < STUDENT_COUNT - i - 1; ++j) {
            if(students[j].points > students[j + 1].points) {
                std::swap(students[j], students[j + 1]);
            }
        }
    }
    (void)students;
}

void print(const Student& s) {
    std::cout << "ID: " << s.id
              << ", Name: " << s.name
              << ", Points: " << s.points << '\n';
}
