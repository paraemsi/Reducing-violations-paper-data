#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Prevent adding a student who is already in the roster (any grade)
    for (const auto& [g, names_list] : students_) {
        if (std::find(names_list.begin(), names_list.end(), name) != names_list.end()) {
            return false;  // Student already exists in the roster
        }
    }

    auto& names_list = students_[grade];
    names_list.push_back(name);
    std::sort(names_list.begin(), names_list.end());
    return true;
}

std::map<int, std::vector<std::string>> school::roster() const {
    return students_;
}

std::vector<std::string> school::grade(int grade_number) const {
    auto it = students_.find(grade_number);
    if (it == students_.end()) {
        return {};
    }
    return it->second;
}

}  // namespace grade_school
