#include "tests_checking.h"

#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> students_works;
    for (auto [name, side] : student_actions) {
        if (side == Side::Top) {
            students_works.push_front(name);
        } else {
            students_works.push_back(name);
        }
    }
    std::vector<std::string> result;
    for (auto index : queries) {
        result.push_back(students_works[index - 1]);
    }
    return result;
}
