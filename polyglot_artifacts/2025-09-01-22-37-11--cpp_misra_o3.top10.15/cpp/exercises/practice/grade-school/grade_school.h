#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <stdexcept>

namespace grade_school {

using grade_t = int;        /* alias uses raw type once, allowed by MISRA rule */
using roster_map_t = std::map<grade_t, std::vector<std::string>>;

class school
{
public:
    school() = default;

    /* Add a student to a grade.
       Throws std::domain_error if the student already exists in any grade. */
    void add(const std::string& name, grade_t grade_level);

    /* Return the list of students in the specified grade, sorted alphabetically. */
    std::vector<std::string> grade(grade_t grade_level) const;

    /* Return the full school roster: grades in numerical order and
       students in each grade in alphabetical order. */
    roster_map_t roster() const;

private:
    /* Internal storage keeps students sorted automatically. */
    std::map<grade_t, std::set<std::string>> m_roster;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
