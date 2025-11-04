#include "grade_school.h"
#include <utility>

namespace grade_school {

void school::add(const std::string& name, grade_t grade_level)
{
    /* Ensure the student is present in at most one grade.                       */
    for (auto it{data_.begin()}; it != data_.end(); ++it) {
        students_set_t& students{it->second};
        const auto student_it{students.find(name)};
        if (student_it != students.end()) {
            if (it->first == grade_level) {
                /* Student already in the requested grade – nothing to change.   */
                return;
            }

            /* Remove the student from the previous grade before re-inserting.   */
            students.erase(student_it);
            if (students.empty()) {
                data_.erase(it);
            }
            break;
        }
    }

    /* Insert the student into the requested grade (ordered automatically).      */
    data_[grade_level].insert(name);
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> full_roster{};

    for (const auto& grade_entry : data_) {
        const grade_t current_grade{grade_entry.first};
        const students_set_t& students{grade_entry.second};

        std::vector<std::string> names{students.begin(), students.end()};
        full_roster.emplace(current_grade, std::move(names));
    }

    return full_roster;
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    std::vector<std::string> names{};

    const auto it{data_.find(grade_level)};
    if (it != data_.end()) {
        const students_set_t& students{it->second};
        names.assign(students.begin(), students.end());
    }

    return names;
}

}  // namespace grade_school
