#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, school::grade_t grade) {
    // Enforce global uniqueness: a student can appear at most once in the roster.
    if (all_students_.count(name) != 0) {
        return false;
    }

    auto& names = by_grade_[grade];
    auto insert_result = names.insert(name);
    bool inserted = insert_result.second;
    if (inserted) {
        all_students_.insert(name);
    }
    return inserted;
}

std::vector<std::string> school::grade(school::grade_t grade) const {
    std::vector<std::string> result;
    auto it = by_grade_.find(grade);
    if (it == by_grade_.end()) {
        return result;
    }
    result.assign(it->second.begin(), it->second.end());
    return result;
}

std::map<school::grade_t, std::vector<std::string>> school::roster() const {
    std::map<school::grade_t, std::vector<std::string>> out;
    for (const auto& entry : by_grade_) {
        const school::grade_t g = entry.first;
        const auto& names = entry.second;
        out[g] = std::vector<std::string>(names.begin(), names.end());
    }
    return out;
}

}  // namespace grade_school
