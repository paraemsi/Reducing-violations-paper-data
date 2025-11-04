#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check if student already exists in any grade
    if (m_all_students.count(name) > 0) {
        return false;
    }
    m_roster[grade].insert(name);
    m_all_students.insert(name);
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    std::vector<std::string> students;
    auto it = m_roster.find(grade);
    if (it != m_roster.end()) {
        students.assign(it->second.begin(), it->second.end());
    }
    return students;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& [grade, students] : m_roster) {
        result[grade] = std::vector<std::string>(students.begin(), students.end());
    }
    return result;
}

}  // namespace grade_school
