#include "grade_school.h"

#include <algorithm>
#include <stdexcept>
#include <string>

namespace grade_school {

const school::roster_t& school::roster() const {
    return roster_;
}

void school::add(const std::string& name, int grade) {
    // prevent duplicate student in any grade
    for (const auto& grade_students_pair : roster_) {
        const auto& students = grade_students_pair.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            throw std::domain_error{"student already added"};
        }
    }

    auto& students = roster_[grade];      // creates grade if it does not yet exist
    students.push_back(name);
    std::sort(students.begin(), students.end());
}

std::vector<std::string> school::grade(int grade) const {
    auto it = roster_.find(grade);
    if (it == roster_.end()) {
        return {};
    }
    return it->second;    // already sorted during insertion
}

}  // namespace grade_school
