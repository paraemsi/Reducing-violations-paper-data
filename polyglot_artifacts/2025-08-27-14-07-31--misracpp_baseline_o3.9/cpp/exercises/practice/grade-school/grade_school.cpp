#include "grade_school.h"
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // Ensure the student does not already exist in any grade.
    for (const auto& grade_students : records_) {
        const auto& students = grade_students.second;
        if (students.find(name) != students.end()) {
            throw std::domain_error{"student already added"};
        }
    }
    // Insert the student; std::set keeps the names sorted automatically.
    records_[grade].insert(name);
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& grade_students : records_) {
        int grade = grade_students.first;
        const auto& students = grade_students.second;
        result[grade] = {students.begin(), students.end()};
    }
    return result;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = records_.find(grade);
    if (it == records_.end()) {
        return {};
    }
    return {it->second.begin(), it->second.end()};
}

}  // namespace grade_school
