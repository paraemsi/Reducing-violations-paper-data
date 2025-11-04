#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade_level) {
    // Reject duplicate student names
    if (m_student_grade.count(name) != 0) {
        return false;
    }
    m_student_grade[name] = grade_level;
    m_roster[grade_level].insert(name);
    return true;
}

std::vector<std::string> school::grade(int grade_level) const {
    auto it = m_roster.find(grade_level);
    if (it == m_roster.end()) {
        return {};
    }
    return std::vector<std::string>(it->second.begin(), it->second.end());
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& grade_pair : m_roster) {
        int grade = grade_pair.first;
        const auto& students_set = grade_pair.second;
        result.emplace(grade, std::vector<std::string>(students_set.begin(), students_set.end()));
    }
    return result;
}

}  // namespace grade_school
