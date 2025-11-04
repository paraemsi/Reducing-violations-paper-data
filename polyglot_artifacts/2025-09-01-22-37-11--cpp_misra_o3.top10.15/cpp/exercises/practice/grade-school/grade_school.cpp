#include "grade_school.h"

namespace grade_school {

/* Add a student while enforcing uniqueness across the whole school. */
void school::add(const std::string& name, grade_t grade_level)
{
    /* Check every grade to ensure the student is not already enrolled. */
    for(const auto& [unused_grade, students] : m_roster) {
        (void)unused_grade; /* suppress unused-variable warning */

        if(students.find(name) != students.end()) {
            throw std::domain_error("student already enrolled");
        }
    }

    /* Insert the student into the appropriate grade. */
    (void)m_roster[grade_level].insert(name);
}

/* Return the roster for a single grade. */
std::vector<std::string> school::grade(grade_t grade_level) const
{
    std::vector<std::string> result{};

    const auto it{m_roster.find(grade_level)};
    if(it != m_roster.end()) {
        result.assign(it->second.begin(), it->second.end());
    }

    return result;
}

/* Return the complete roster with grades and names properly ordered. */
roster_map_t school::roster() const
{
    roster_map_t ordered_roster{};

    for(const auto& [g, students_set] : m_roster) {
        ordered_roster[g] = std::vector<std::string>{students_set.begin(), students_set.end()};
    }

    return ordered_roster;
}

}  // namespace grade_school
