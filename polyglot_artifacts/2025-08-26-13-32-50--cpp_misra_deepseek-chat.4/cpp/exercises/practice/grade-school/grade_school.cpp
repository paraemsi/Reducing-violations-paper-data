#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, std::int32_t grade) {
    // Check if the student already exists in any grade
    for (const auto& entry : students_by_grade) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            // Student found, don't add
            return;
        }
    }
    
    // Add to the appropriate grade
    auto& students = students_by_grade[grade];
    // Insert the name in sorted position to maintain order
    students.insert(
        std::upper_bound(students.begin(), students.end(), name),
        name
    );
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const {
    return students_by_grade;
}

std::vector<std::string> school::grade(std::int32_t grade_number) const {
    auto it = students_by_grade.find(grade_number);
    if (it != students_by_grade.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

}  // namespace grade_school
