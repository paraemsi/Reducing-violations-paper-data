#include "grade_school.h"

#include <algorithm>
#include <stdexcept>

namespace grade_school {

void school::add(const std::string& name, grade_t grade_number)
{
    if(contains_student(name)) {
        // Duplicate entries are not permitted by specification – raise error
        throw std::domain_error("duplicate student");
    }

    auto& grade_vec = students_[grade_number];
    grade_vec.push_back(name);
    std::sort(grade_vec.begin(), grade_vec.end());
}

std::vector<std::string> school::grade(grade_t grade_number) const
{
    const auto iter = students_.find(grade_number);
    if(iter != students_.end()) {
        return iter->second;
    } else {
        return {};
    }
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    return students_;
}

bool school::contains_student(const std::string& name) const
{
    for(const auto& entry : students_) {
        if(std::find(entry.second.begin(), entry.second.end(), name) != entry.second.end()) {
            return true;
        }
    }
    return false;
}

}  // namespace grade_school
