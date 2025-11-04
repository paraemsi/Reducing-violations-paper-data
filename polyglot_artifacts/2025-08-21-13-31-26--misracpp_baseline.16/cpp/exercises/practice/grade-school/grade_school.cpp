#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Prevent adding the same student to any grade more than once
    if (m_student_grade.count(name) > 0) {
        return false;
    }
    m_roster[grade].push_back(name);
    m_student_grade[name] = grade;
    // Keep the students in this grade sorted
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

std::map<int, std::vector<std::string> > school::roster() const {
    std::map<int, std::vector<std::string> > sorted_roster;
    for (const auto& entry : m_roster) {
        std::vector<std::string> students = entry.second;
        std::sort(students.begin(), students.end());
        sorted_roster[entry.first] = students;
    }
    return sorted_roster;
}

}  // namespace grade_school
