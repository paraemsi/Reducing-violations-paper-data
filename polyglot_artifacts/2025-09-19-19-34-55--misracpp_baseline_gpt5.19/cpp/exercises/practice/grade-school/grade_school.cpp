#include "grade_school.h"
#include <utility>

namespace grade_school {

bool school::add(const std::string& name, int grade) {
    if (contains_student(name)) {
        return false;
    }
    by_grade_[grade].insert(name);
    return true;
}

std::map<int, std::vector<std::string>> school::roster() const {
    std::map<int, std::vector<std::string>> result;
    for (const auto& pair : by_grade_) {
        int grade_key = pair.first;
        const std::set<std::string>& names_set = pair.second;
        std::vector<std::string> names;
        names.reserve(names_set.size());
        for (const auto& n : names_set) {
            names.push_back(n);
        }
        result.emplace(grade_key, std::move(names));
    }
    return result;
}

std::vector<std::string> school::grade(int grade) const {
    std::vector<std::string> names;
    auto it = by_grade_.find(grade);
    if (it == by_grade_.end()) {
        return names;
    }
    names.reserve(it->second.size());
    for (const auto& n : it->second) {
        names.push_back(n);
    }
    return names;
}

bool school::contains_student(const std::string& name) const {
    for (const auto& pair : by_grade_) {
        const std::set<std::string>& names_set = pair.second;
        if (names_set.find(name) != names_set.end()) {
            return true;
        }
    }
    return false;
}

}  // namespace grade_school
