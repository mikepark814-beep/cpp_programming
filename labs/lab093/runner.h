#ifndef RUNNER_H
#define RUNNER_H

#include <string>
#include <vector>

struct Runner {
    std::string name;
    int minutes;   // 완주 시간 (분)
    int age;
};

// 정렬 기준:
//  1) minutes 오름차순
//  2) age 내림차순 (연장자 우대)
//  3) name 오름차순
void rank_runners(std::vector<Runner>& v);

#endif // RUNNER_H
