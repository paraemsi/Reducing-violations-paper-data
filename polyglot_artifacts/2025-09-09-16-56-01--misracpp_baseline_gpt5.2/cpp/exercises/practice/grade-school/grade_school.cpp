#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // Enforce unique student names across the entire school.
    if (m_students.find(name) != m_students.end()) {
        throw std::invalid_argument("Duplicate student enrollment attempted");
    }

    auto& students = m_roster[grade];
    auto it = std::lower_bound(students.begin(), students.end(), name);
    students.insert(it, name);
    m_students.insert(name);
}

std::vector<std::string> school::grade(int grade) const {
    auto it = m_roster.find(grade);
    if (it == m_roster.end()) {
        return {};
    }
    return it->second;
}

std::map<int, std::vector<std::string>> school::roster() const {
    return m_roster;
}

}  // namespace grade_school
