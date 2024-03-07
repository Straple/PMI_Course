#include "sort_students.h"
#include <tuple>

auto BuildTieForName(const Student& student) {
    return std::tie(student.last_name, student.name, student.birth_date.year, student.birth_date.month,
                    student.birth_date.day);
}

auto BuildTieForDate(const Student& student) {
    return std::tie(student.birth_date.year, student.birth_date.month, student.birth_date.day, student.last_name,
                    student.name);
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(),
                  [&](const Student& lhs, const Student& rhs) { return BuildTieForDate(lhs) < BuildTieForDate(rhs); });
    } else {
        std::sort(students.begin(), students.end(),
                  [&](const Student& lhs, const Student& rhs) { return BuildTieForName(lhs) < BuildTieForName(rhs); });
    }
}
