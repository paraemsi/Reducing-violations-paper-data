#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_level) {
    if ((m_students.find(name) != m_students.end())) {
        return false;
    } else {
        auto& list = m_roster[grade_level];
        list.push_back(name);
        std::sort(list.begin(), list.end());
        (void)m_students.insert(name);
        return true;
    }
}

std::vector<std::string> school::grade(grade_t grade_level) const {
    const auto it = m_roster.find(grade_level);
    if ((it != m_roster.end())) {
        return it->second;
    } else {
        return std::vector<std::string>{};
    }
}

roster_t school::roster() const {
    return m_roster;
}

}  // namespace grade_school
