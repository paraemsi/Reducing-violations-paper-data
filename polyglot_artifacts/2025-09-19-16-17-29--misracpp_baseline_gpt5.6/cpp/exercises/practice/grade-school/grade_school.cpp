#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Prevent the same student from being added more than once to the roster (any grade).
    for (const auto& kv : students_) {
        const auto& names = kv.second;
        if (std::find(names.begin(), names.end(), name) != names.end()) {
            return false;
        }
    }

    // Insert and keep the grade's roster sorted alphabetically.
    auto& names = students_[grade];
    names.push_back(name);
    std::sort(names.begin(), names.end());
    names.erase(std::unique(names.begin(), names.end()), names.end());
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = students_.find(grade);
    if (it == students_.end()) {
        return {};
    }
    return it->second; // Already kept sorted on insert.
}

std::map<int, std::vector<std::string>> school::roster() const {
    // Grades are naturally sorted by std::map keys.
    std::map<int, std::vector<std::string>> result;
    for (const auto& kv : students_) {
        auto names = kv.second;
        std::sort(names.begin(), names.end());
        names.erase(std::unique(names.begin(), names.end()), names.end());
        result.emplace(kv.first, std::move(names));
    }
    return result;
}

}  // namespace grade_school
