#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Prevent duplicate student names across all grades
    if (m_all_students.find(name) != m_all_students.end()) {
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
    // Iterate without structured bindings to preserve compatibility with pre-C++17 compilers
    for (const auto& kv : m_roster) {
        const int grade = kv.first;
        const std::set<std::string>& students_set = kv.second;
        result[grade] = std::vector<std::string>(students_set.begin(), students_set.end());
    }
    return result;
}

}  // namespace grade_school
