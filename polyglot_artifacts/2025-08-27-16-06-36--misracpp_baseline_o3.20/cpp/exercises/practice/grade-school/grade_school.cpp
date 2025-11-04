#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check if the student already exists anywhere in the roster.
    for (const auto& kv : roster_) {
        const auto& students = kv.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            return false;
        }
    }

    auto& students = roster_[grade];

    // Extra safeguard (should not be necessary due to previous check).
    if (std::find(students.begin(), students.end(), name) != students.end()) {
        return false;
    }

    students.push_back(name);
    std::sort(students.begin(), students.end());
    return true;
}

const school::roster_t& school::roster() const {
    return roster_;
}

const std::vector<std::string>& school::grade(int grade) const {
    static const std::vector<std::string> empty{};
    auto it = roster_.find(grade);
    if (it == roster_.end()) {
        return empty;
    }
    return it->second;
}

}  // namespace grade_school
