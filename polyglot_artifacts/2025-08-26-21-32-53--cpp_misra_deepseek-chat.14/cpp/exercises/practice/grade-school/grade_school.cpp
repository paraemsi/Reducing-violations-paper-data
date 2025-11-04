#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <map>

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // Check if the grade can be safely cast to std::int32_t
    // Since int may be different sizes on different platforms, we need to ensure it fits
    // According to the rules, we need to use static_cast
    const std::int32_t fixed_grade = static_cast<std::int32_t>(grade);
    
    // Check if the student is already in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            throw std::runtime_error("Student already exists in the roster");
        }
    }
    
    // Add the student to the specified grade
    // roster_ uses GradeType which is std::int32_t, and fixed_grade is std::int32_t
    // This follows the assignment rules
    roster_[fixed_grade].push_back(name);
    // Sort the students in the grade alphabetically
    std::sort(roster_[fixed_grade].begin(), roster_[fixed_grade].end());
}

const std::vector<std::string>& school::grade(int grade) const {
    static const std::vector<std::string> empty;
    // Cast the input grade to the internal type
    const std::int32_t fixed_grade = static_cast<std::int32_t>(grade);
    auto it = roster_.find(fixed_grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return empty;
}

std::map<int, std::vector<std::string>> school::roster() const {
    // Convert the internal map to the required return type
    std::map<int, std::vector<std::string>> result;
    for (const auto& entry : roster_) {
        // Cast each key from std::int32_t to int
        // This is necessary to match the return type
        result[static_cast<int>(entry.first)] = entry.second;
    }
    return result;
}

}  // namespace grade_school
