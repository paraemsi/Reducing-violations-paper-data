#include "grade_school.h"

namespace grade_school {

void school::add(const std::string& name, int grade) {
    // Enforce global uniqueness: ignore if already enrolled in the school.
    if (all_students_.find(name) != all_students_.end()) {
        return;
    }
    roster_[grade].insert(name);
    all_students_.insert(name);
}

std::vector<std::string> school::grade(int g) const {
    std::vector<std::string> result;
    auto it = roster_.find(g);
    if (it != roster_.end()) {
        // std::set is already sorted; copy preserves order.
        result.assign(it->second.begin(), it->second.end());
    }
    return result;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> out;
    for (const auto& entry : roster_) {
        const auto& students_set = entry.second;
        out[entry.first] = std::vector<std::string>(students_set.begin(), students_set.end());
    }
    return out;
}

}  // namespace grade_school
