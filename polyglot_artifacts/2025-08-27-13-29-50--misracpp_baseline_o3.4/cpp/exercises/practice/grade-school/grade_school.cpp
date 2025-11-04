#include "grade_school.h"

#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // If the student already exists anywhere, do nothing.
    for (const auto& entry : m_students) {
        if (entry.second.find(name) != entry.second.end()) {
            return;
        }
    }
    m_students[grade].insert(name);
}

std::vector<std::string> school::grade(int grade) const {
    std::vector<std::string> result;
    auto it = m_students.find(grade);
    if (it != m_students.end()) {
        result.assign(it->second.begin(), it->second.end());
    }
    return result; // already sorted thanks to std::set
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& entry : m_students) {
        result[entry.first].assign(entry.second.begin(), entry.second.end()); // copy, preserves order
    }
    return result;
}

}  // namespace grade_school
