#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check if student already exists in any grade
    for (const auto& [g, names] : students_) {
        if (std::find(names.begin(), names.end(), name) != names.end()) {
            return false; // Student already present
        }
    }
    // Add student to the grade
    students_[grade].push_back(name);
    // Keep the vector sorted
    std::sort(students_[grade].begin(), students_[grade].end());
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = students_.find(grade);
    if (it != students_.end()) {
        return it->second;
    }
    return {};
}

std::vector<std::string> school::roster() const {
    std::vector<std::string> all;
    for (const auto& [grade, names] : students_) {
        all.insert(all.end(), names.begin(), names.end());
    }
    return all;
}

std::map<int, std::vector<std::string>> school::grades() const {
    return students_;
}

}  // namespace grade_school
