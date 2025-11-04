#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // First, check if the student exists in any grade
    // The instructions say "each student cannot be added more than once to a grade or the roster"
    // So we need to ensure the student isn't in any grade, not just the target grade
    for (const auto& entry : roster_) {
        const auto& students = entry.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            // Student found in some grade, don't add
            return;
        }
    }
    
    // If not found, add to the specified grade and sort
    auto& students = roster_[grade];
    // Insert the name and sort
    students.push_back(name);
    std::sort(students.begin(), students.end());
}

const std::map<std::uint32_t, std::vector<std::string>>& school::roster() const {
    return roster_;
}

std::vector<std::string> school::grade(std::uint32_t grade) const {
    auto it = roster_.find(grade);
    if (it != roster_.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
