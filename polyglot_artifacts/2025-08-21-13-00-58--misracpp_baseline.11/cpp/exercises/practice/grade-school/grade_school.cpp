#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check if student already exists in any grade
    for (const auto& [g, students] : m_roster) {
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            return false; // Student already present
        }
    }
    // Add student to the grade
    m_roster[grade].push_back(name);
    // Keep students sorted in the grade
    std::sort(m_roster[grade].begin(), m_roster[grade].end());
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = m_roster.find(grade);
    if (it != m_roster.end()) {
        return it->second;
    }
    return {};
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> sorted_roster;
    for (const auto& [grade, students] : m_roster) {
        std::vector<std::string> sorted_students = students;
        std::sort(sorted_students.begin(), sorted_students.end());
        sorted_roster[grade] = sorted_students;
    }
    return sorted_roster;
}

}  // namespace grade_school
