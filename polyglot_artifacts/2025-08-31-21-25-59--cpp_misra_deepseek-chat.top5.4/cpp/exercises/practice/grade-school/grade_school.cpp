#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // First, check if the student exists in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            throw std::runtime_error("Student already exists in the roster");
        }
    }
    
    // Add to the specified grade
    auto& students_in_grade = roster_[grade];
    students_in_grade.push_back(name);
    std::sort(students_in_grade.begin(), students_in_grade.end());
}

const std::map<std::uint32_t, std::vector<std::string>>& school::roster() const {
    return roster_;
}

const std::vector<std::string>& school::grade(std::uint32_t grade_num) const {
    static const std::vector<std::string> empty;
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    }
    return empty;
}

}  // namespace grade_school
