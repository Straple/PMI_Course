#include "admission.h"

bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Applicant& lhs, const Applicant& rhs) {
    return lhs.points > rhs.points ||
           (lhs.points == rhs.points &&
            std::tie(lhs.student.birth_date, lhs.student.name) < std::tie(rhs.student.birth_date, rhs.student.name));
}

bool operator<(const Student& lhs, const Student& rhs) {
    return std::tie(lhs.name, lhs.birth_date) < std::tie(rhs.name, rhs.birth_date);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> applicants_ptr;
    applicants_ptr.reserve(applicants.size());
    for (auto& applicant : applicants) {
        applicants_ptr.emplace_back(&applicant);
    }
    std::sort(applicants_ptr.begin(), applicants_ptr.end(),
              [](const Applicant* lhs, const Applicant* rhs) { return *lhs < *rhs; });

    std::unordered_map<std::string, size_t> university_index;
    for (std::size_t index = 0; index < universities.size(); index++) {
        university_index[universities[index].name] = index;
    }

    std::vector<std::size_t> university_students_count(universities.size());

    AdmissionTable result;

    for (const Applicant* enrollee_ptr : applicants_ptr) {
        for (const std::string& university_name : enrollee_ptr->wish_list) {
            std::size_t index = university_index[university_name];
            if (university_students_count[index] < universities[index].max_students) {
                university_students_count[index]++;
                result[university_name].push_back(&enrollee_ptr->student);
                break;
            }
        }
    }
    for (auto [university_name, students] : result) {
        std::sort(students.begin(), students.end(), [](const Student* lhs, const Student* rhs) { return *lhs < *rhs; });
    }
    return result;
}
