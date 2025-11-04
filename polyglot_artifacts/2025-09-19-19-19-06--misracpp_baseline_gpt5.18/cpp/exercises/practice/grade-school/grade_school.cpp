#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Disallow duplicates anywhere in the school.
    if (students_.find(name) != students_.end()) {
        return false;
    }

    auto& students = roster_[grade];
    students.push_back(name);
    std::sort(students.begin(), students.end());

    students_.insert(name);
    return true;
}

std::map<int, std::vector<std::string>> school::roster() const {
    return roster_;
}

std::vector<std::string> school::grade(int grade_number) const {
    auto it = roster_.find(grade_number);
    if (it == roster_.end()) {
        return {};
    }
    return it->second;
}

}  // namespace grade_school
