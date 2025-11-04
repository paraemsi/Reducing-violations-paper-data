#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, std::int32_t grade) {
    // Check if the student is already in any grade
    auto it = student_to_grade_.find(name);
    if (it != student_to_grade_.end()) {
        // Student already exists, don't add again
        return;
    }
    
    // Add to the appropriate grade
    auto& students = roster_[grade];
    // Insert in sorted order
    auto insert_pos = std::lower_bound(students.begin(), students.end(), name);
    students.insert(insert_pos, name);
    // Track which grade the student is in
    student_to_grade_[name] = grade;
}

std::vector<std::string> school::grade(std::int32_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        // Return a copy which is already sorted due to our insertion method
        return it->second;
    }
    return std::vector<std::string>();
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const {
    // The map is ordered by key (grade), and each vector is already sorted
    return roster_;
}

}  // namespace grade_school
