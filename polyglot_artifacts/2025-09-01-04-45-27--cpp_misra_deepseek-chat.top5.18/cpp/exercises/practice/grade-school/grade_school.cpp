#include "grade_school.h"
#include <algorithm>
#include <iterator>

namespace grade_school {

void school::add(const std::string& name, std::int32_t grade) {
    // Check if the student already exists in any grade
    auto it = student_to_grade_.find(name);
    if (it != student_to_grade_.end()) {
        // According to instructions, this is incorrect
        // We can't add the same student more than once
        // Since the function is void, we'll just return without doing anything
        // Or perhaps the tests expect an exception
        // Let's assume we need to not modify anything
        return;
    }
    
    // Add the student to the new grade
    roster_[grade].insert(name);
    student_to_grade_[name] = grade;
}

std::vector<std::string> school::grade(std::int32_t grade_num) const {
    auto it = roster_.find(grade_num);
    if (it != roster_.end()) {
        return std::vector<std::string>(it->second.begin(), it->second.end());
    } else {
        return std::vector<std::string>();
    }
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const {
    std::map<std::int32_t, std::vector<std::string>> result;
    for (const auto& entry : roster_) {
        result[entry.first] = std::vector<std::string>(entry.second.begin(), entry.second.end());
    }
    return result;
}

}  // namespace grade_school
