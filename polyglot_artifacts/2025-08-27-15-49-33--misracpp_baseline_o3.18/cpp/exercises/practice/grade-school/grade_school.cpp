#include "grade_school.h"

#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string &name, int grade) {
    // Reject duplicate students already present in any grade.
    for (const auto &[g, students] : m_roster) {
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            throw std::domain_error("Student already added.");
        }
    }

    // Insert student into the requested grade.
    auto &students = m_roster[grade];
    students.push_back(name);

    // Keep the vector sorted so all retrievals are already ordered.
    std::sort(students.begin(), students.end());
}

const roster_t& school::roster() const {
    return m_roster; // std::map maintains grade order automatically
}

std::vector<std::string> school::grade(int grade) const {
    auto it = m_roster.find(grade);
    if (it == m_roster.end()) {
        return {};
    }
    return it->second;
}

}  // namespace grade_school
