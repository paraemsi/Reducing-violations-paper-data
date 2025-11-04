#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check if student already exists in any grade
    if (m_all_students.count(name) > 0) {
        return false;
    }
    m_students[grade].insert(name);
    m_all_students.insert(name);
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    std::vector<std::string> result;
    auto it = m_students.find(grade);
    if (it != m_students.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& [grade, students] : m_students) {
        result[grade] = std::vector<std::string>(students.begin(), students.end());
    }
    return result;
}

}  // namespace grade_school
