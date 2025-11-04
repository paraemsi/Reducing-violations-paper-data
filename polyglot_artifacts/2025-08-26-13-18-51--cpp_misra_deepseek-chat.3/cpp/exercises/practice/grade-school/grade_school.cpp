#include "grade_school.h"
#include <algorithm>
#include <string>
#include <vector>
#include <map>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student already exists in any grade
    for (const auto& pair : roster_) {
        const auto& students = pair.second;
        if (std::find(students.begin(), students.end(), name) != students.end()) {
            // Student found, don't add them
            return;
        }
    }
    
    // Add to the specified grade
    auto& students = roster_[grade];
    students.push_back(name);
    std::sort(students.begin(), students.end());
}

const std::map<std::uint32_t, std::vector<std::string>>& school::roster() const {
    return roster_;
}

std::vector<std::string> school::grade(std::uint32_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

}  // namespace grade_school
