#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade_level) {
    // Prevent a student from being in more than one grade.
    for (const auto& [grade, students] : students_by_grade_) {
        if (students.find(name) != students.end()) {
            return false; // student already present somewhere
        }
    }

    students_by_grade_[grade_level].insert(name);
    return true;
}

std::vector<std::string> school::grade(int grade_level) const {
    std::vector<std::string> result;
    auto it = students_by_grade_.find(grade_level);
    if (it != students_by_grade_.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result; // empty if grade not found
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> full_roster;
    for (const auto& [grade, students_set] : students_by_grade_) {
        full_roster[grade].assign(students_set.begin(), students_set.end());
    }
    return full_roster;
}

}  // namespace grade_school
