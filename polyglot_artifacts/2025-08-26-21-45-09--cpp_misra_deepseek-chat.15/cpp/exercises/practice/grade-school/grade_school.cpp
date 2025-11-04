#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, std::int32_t grade) {
    // Check if the student already exists in the entire school
    // If they do, don't add them again
    if (all_students_.find(name) != all_students_.end()) {
        return;
    }
    
    // Add to the appropriate grade
    auto& grade_students = roster_[grade];
    grade_students.push_back(name);
    // Sort the names alphabetically
    std::sort(grade_students.begin(), grade_students.end());
    // Add to all students
    all_students_.insert(name);
}

std::vector<std::string> school::grade(std::int32_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
