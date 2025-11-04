#include "grade_school.h"
#include <algorithm>
#include <cstdint>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check if grade is non-negative
    if (grade < 0) {
        return false;
    }
    
    // Convert to fixed-width type
    const std::uint32_t fixed_grade = static_cast<std::uint32_t>(grade);
    
    // Check if the student already exists in the target grade
    // According to the instructions, a student can't be in the roster more than once
    // So we need to check all grades
    for (const auto& entry : students_by_grade) {
        const auto& students = entry.second;
        // Use binary search since the vector is always sorted
        if (std::binary_search(students.begin(), students.end(), name)) {
            return false;
        }
    }
    
    // Add to the appropriate grade
    auto& grade_students = students_by_grade[fixed_grade];
    // Insert the name in sorted order
    const auto insert_pos = std::lower_bound(grade_students.begin(), grade_students.end(), name);
    grade_students.insert(insert_pos, name);
    return true;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& entry : students_by_grade) {
        // The key in the result map needs to be int to match the interface
        // This is a widening conversion which is allowed
        result[static_cast<int>(entry.first)] = entry.second;
    }
    return result;
}

std::vector<std::string> school::grade(int grade) const {
    if (grade < 0) {
        return {};
    }
    // Convert to fixed-width type
    const std::uint32_t fixed_grade = static_cast<std::uint32_t>(grade);
    const auto it = students_by_grade.find(fixed_grade);
    if (it != students_by_grade.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
