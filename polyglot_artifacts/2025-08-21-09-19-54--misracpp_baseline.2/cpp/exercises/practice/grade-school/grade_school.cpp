#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check if student already exists in any grade
    for (const auto& [g, students] : m_students) {
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            return false; // Student already present
        }
    }
    // Add student to the grade
    m_students[grade].push_back(name);
    // Keep the vector sorted
    std::sort(m_students[grade].begin(), m_students[grade].end());
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = m_students.find(grade);
    if (it != m_students.end()) {
        return it->second;
    }
    return {};
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& [grade, students] : m_students) {
        result[grade] = students;
    }
    return result;
}

}  // namespace grade_school
