#include "grade_school.h"

namespace grade_school {

auto school::add(const std::string& name, std::int32_t grade) -> bool
{
    /* Prevent duplicate enrolment */
    if (student_to_grade_.find(name) != student_to_grade_.end()) {
        return false;
    }

    (void)student_to_grade_.emplace(name, grade);
    (void)grade_to_names_[grade].insert(name);
    return true;
}

auto school::roster() const -> std::vector<std::string>
{
    std::vector<std::string> result{};

    /* std::map keeps grades ordered ascending; std::set keeps names alphabetical */
    for (const auto& grade_pair : grade_to_names_) {
        result.insert(result.end(), grade_pair.second.begin(), grade_pair.second.end());
    }

    return result;
}

auto school::grade(std::int32_t grade) const -> std::vector<std::string>
{
    const auto it{grade_to_names_.find(grade)};
    if (it == grade_to_names_.end()) {
        return {};
    }

    std::vector<std::string> students{};
    students.assign(it->second.begin(), it->second.end());
    return students;
}

}  // namespace grade_school
