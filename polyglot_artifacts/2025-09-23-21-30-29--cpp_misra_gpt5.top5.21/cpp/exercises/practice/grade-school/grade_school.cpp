#include "grade_school.h"
#include <algorithm>
#include <utility>

namespace grade_school {

void school::add(const std::string& student, grade_t grade_value) {
    if ((all_students_.find(student) != all_students_.end())) {
        // Duplicate; do not add again
    } else {
        (void)all_students_.insert(student);
        grade_to_students_[grade_value].insert(student);
    }
}

std::vector<std::string> school::grade(grade_t grade_value) const {
    std::vector<std::string> result{};
    const auto it = grade_to_students_.find(grade_value);
    if ((it != grade_to_students_.end())) {
        result.assign(it->second.begin(), it->second.end());
    } else {
        // No students in this grade
    }
    return result;
}

std::map<grade_t, std::vector<std::string>> school::roster() const {
    std::map<grade_t, std::vector<std::string>> result{};
    for (const auto& entry : grade_to_students_) {
        std::vector<std::string> students{};
        students.assign(entry.second.begin(), entry.second.end());
        (void)result.emplace(entry.first, std::move(students));
    }
    return result;
}

}  // namespace grade_school
