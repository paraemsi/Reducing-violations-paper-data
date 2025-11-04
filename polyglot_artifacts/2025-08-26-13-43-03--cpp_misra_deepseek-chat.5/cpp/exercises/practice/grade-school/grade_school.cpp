#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student is already in any grade
    auto it = student_to_grade_.find(name);
    if (it != student_to_grade_.end()) {
        // If the student already exists, do nothing
        return;
    }
    
    // Add the student to the specified grade
    // Insert in sorted order to avoid sorting every time
    auto& students = roster_[grade];
    // Find where to insert to maintain sorted order
    auto insert_pos = std::lower_bound(students.begin(), students.end(), name);
    students.insert(insert_pos, name);
    // Track which grade the student is in
    student_to_grade_[name] = grade;
}

const std::map<std::uint32_t, std::vector<std::string>>& school::roster() const {
    return roster_;
}

std::vector<std::string> school::grade(std::uint32_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

}  // namespace grade_school
