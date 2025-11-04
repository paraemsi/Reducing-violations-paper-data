#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    auto& students = students_by_grade_[grade];
    // Check if already present
    if (std::find(students.begin(), students.end(), name) != students.end()) {
        return false;
    }
    students.push_back(name);
    std::sort(students.begin(), students.end());
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = students_by_grade_.find(grade);
    if (it != students_by_grade_.end()) {
        return it->second;
    }
    return {};
}

std::vector<std::string> school::roster() const {
    std::vector<std::string> all_students;
    for (const auto& [grade, students] : students_by_grade_) {
        all_students.insert(all_students.end(), students.begin(), students.end());
    }
    return all_students;
}

std::map<int, std::vector<std::string> > school::grades() const {
    return students_by_grade_;
}

}  // namespace grade_school
