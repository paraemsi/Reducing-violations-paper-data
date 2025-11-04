#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    // Disallow duplicates anywhere in the school.
    if (student_grade_.count(name) > 0) {
        return false;
    }

    grades_[grade].insert(name);
    student_grade_[name] = grade;
    return true;
}

std::vector<std::string> school::grade(int grade) const {
    auto it = grades_.find(grade);
    if (it == grades_.end()) {
        return {};
    }
    return {it->second.begin(), it->second.end()};
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& grade_entry : grades_) {
        const int grade_number = grade_entry.first;
        const auto& names_set  = grade_entry.second;
        result.emplace(grade_number,
                       std::vector<std::string>{names_set.begin(), names_set.end()});
    }
    return result;
}

}  // namespace grade_school
