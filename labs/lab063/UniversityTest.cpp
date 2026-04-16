#include <memory>
#include "University.hpp"
#include "Department.hpp"
#include "Faculty.hpp"

int main() {
    auto faculty = std::make_shared<Faculty>("Computer Science", 10);

    University univ("Pusan National University");
    univ.addDepartment(Department("Math"));
    univ.addDepartment(Department("Information and Biomedical Engineering", faculty));
    univ.addDepartment(Department("Computer Science and Engineering", faculty));

    univ.printInfo();
    return 0;
}
