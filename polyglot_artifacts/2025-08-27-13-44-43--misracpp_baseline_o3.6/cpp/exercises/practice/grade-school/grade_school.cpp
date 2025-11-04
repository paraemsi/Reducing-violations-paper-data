#include "grade_school.h"

namespace grade_school {

void school::add(const std::string& name, int grade) {
    if (m_student_index_.count(name) > 0) {
        throw std::domain_error("student already added");
    }
    m_roster_[grade].insert(name);
    m_student_index_[name] = grade;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = m_roster_.find(grade);
    if (it == m_roster_.end()) {
        return {};
    }
    return {it->second.begin(), it->second.end()};
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& pair : m_roster_) {
        result[pair.first] = {pair.second.begin(), pair.second.end()};
    }
    return result;
}

}  // namespace grade_school
