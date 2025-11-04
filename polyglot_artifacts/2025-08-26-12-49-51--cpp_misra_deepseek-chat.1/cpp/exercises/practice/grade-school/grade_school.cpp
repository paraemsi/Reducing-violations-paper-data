#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student is already in any grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (students.find(name) != students.end()) {
            // If found, do nothing (student already exists)
            return;
        }
    }
    // Add the student to the specified grade
    roster_[grade].insert(name);
}

std::set<std::string> school::grade(std::uint32_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    }
    return std::set<std::string>();
}

std::map<std::uint32_t, std::set<std::string>> school::roster() const {
    return roster_;
}

}  // namespace grade_school
