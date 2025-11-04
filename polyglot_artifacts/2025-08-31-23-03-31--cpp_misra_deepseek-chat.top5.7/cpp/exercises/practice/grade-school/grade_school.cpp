#include "grade_school.h"
#include <algorithm>
#include <string>
#include <vector>
#include <cstdint>

namespace grade_school {

void school::add(const std::string& name, grade_t grade) {
    // Get reference to the students in the grade
    auto& students = roster_[grade];
    
    // Check if the student is already in the grade using binary search since the list is always sorted
    // This is more efficient and follows the rules
    const auto it = std::lower_bound(students.begin(), students.end(), name);
    if (((it != students.end())) && (((*it) == name))) {
        // Student already exists, don't add again
        return;
    }
    
    // Insert the name in sorted order
    students.insert(it, name);
}

std::vector<std::string> school::grade(grade_t grade_num) const {
    const auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    } else {
        return std::vector<std::string>();
    }
}

std::map<grade_t, std::vector<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
