#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace grade_school {

void school::add(const std::string& name, std::int32_t grade) {
    // Check if the student is already in any grade (the entire roster)
    if (all_students.find(name) != all_students.end()) {
        // Student already exists in the roster, don't add
        return;
    }
    // Check if the student is already in the specific grade (though all_students check above should prevent this)
    // Add to the grade and mark as present in the roster
    students_by_grade[grade].insert(name);
    all_students.insert(name);
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const {
    std::map<std::int32_t, std::vector<std::string>> result;
    for (const auto& entry : students_by_grade) {
        // Convert each set to a vector
        result[entry.first] = std::vector<std::string>(entry.second.begin(), entry.second.end());
    }
    return result;
}

std::vector<std::string> school::grade(std::int32_t grade_num) const {
    auto it = students_by_grade.find(grade_num);
    if (it != students_by_grade.end()) {
        return std::vector<std::string>(it->second.begin(), it->second.end());
    }
    return std::vector<std::string>();
}

}  // namespace grade_school
