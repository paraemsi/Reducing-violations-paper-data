#include "grade_school.h"

namespace grade_school {

void school::add(const std::string& name, grade_t grade_level) noexcept
{
    /* Reject any attempt to add a student that is already enrolled.       */
    if(m_student_to_grade.find(name) != m_student_to_grade.end()) {
        return;
    }

    /* Insert the student into both helper maps.                           */
    (void)m_student_to_grade.insert({name, grade_level});
    (void)m_grade_to_students[grade_level].insert(name);
}

std::map<grade_t, std::vector<std::string>> school::roster() const noexcept
{
    std::map<grade_t, std::vector<std::string>> result {};

    for(const auto& grade_pair : m_grade_to_students) {
        const grade_t grade_value {grade_pair.first};
        const std::set<std::string>& names_set {grade_pair.second};

        std::vector<std::string> names_vec {};
        names_vec.reserve(names_set.size());

        for(const auto& nm : names_set) {
            names_vec.push_back(nm);
        }

        (void)result.insert({grade_value, names_vec});
    }

    return result;
}

std::vector<std::string> school::grade(const grade_t grade_level) const noexcept
{
    const auto it {m_grade_to_students.find(grade_level)};

    if(it == m_grade_to_students.end()) {
        return {};
    }

    const std::set<std::string>& names_set {it->second};

    std::vector<std::string> names_vec {};
    names_vec.reserve(names_set.size());

    for(const auto& nm : names_set) {
        names_vec.push_back(nm);
    }

    return names_vec;
}

}  // namespace grade_school
