#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Check if the student already exists in any grade.
    for (const auto& kv : students_) {
        const auto& list = kv.second;
        if (std::find(list.begin(), list.end(), name) != list.end()) {
            return false; // Duplicate student
        }
    }

    auto& list = students_[grade];
    auto pos = std::lower_bound(list.begin(), list.end(), name);
    list.insert(pos, name); // keep list sorted alphabetically
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = students_.find(grade);
    if (it == students_.end()) {
        return {};
    }
    return it->second; // already sorted
}

std::map<int, std::vector<std::string>> school::roster() const {
    return students_; // std::map keeps keys sorted; vectors kept sorted at insertion
}

}  // namespace grade_school
