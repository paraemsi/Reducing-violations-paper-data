#include "grade_school.h"
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstdint>

namespace grade_school {

void school::add(const std::string& name, std::uint32_t grade) {
    // Check if the student already exists using the all_students_ set
    if (all_students_.find(name) != all_students_.end()) {
        // Student found, don't add
        return;
    }
    
    // Add to the specified grade and track the student
    roster_[grade].insert(name);
    all_students_.insert(name);
}

std::vector<std::string> school::grade(std::uint32_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return std::vector<std::string>(it->second.begin(), it->second.end());
    }
    return {};
}

std::map<std::uint32_t, std::vector<std::string>> school::roster() const {
    std::map<std::uint32_t, std::vector<std::string>> result;
    for (const auto& entry : roster_) {
        result[entry.first] = std::vector<std::string>(entry.second.begin(), entry.second.end());
    }
    return result;
}

}  // namespace grade_school
