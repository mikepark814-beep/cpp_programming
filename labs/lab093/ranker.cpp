#include <vector>
#include <string>
#include <algorithm>

struct Runner {
    std::string name;
    int minutes;
    int age;
};

void rank_runners(std::vector<Runner>& v) {
    std::sort(v.begin(), v.end(),
        [](const Runner& a, const Runner& b) {
            if (a.minutes != b.minutes) return a.minutes < b.minutes;
            if (a.age != b.age)         return a.age > b.age;
            return a.name < b.name;
        }
    );
}