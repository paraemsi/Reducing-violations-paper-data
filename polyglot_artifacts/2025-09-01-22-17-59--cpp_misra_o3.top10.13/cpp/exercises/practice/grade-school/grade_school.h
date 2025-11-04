#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

/*  Alias used for all grade values to comply with MISRA rule that
    forbids use of fundamental signed/unsigned integer type names.   */
using grade_t = std::int32_t;

class school {
public:
    school() = default;

    /*  Add a student to the specified grade.
        If the student is already present in any grade, the call has no
        effect.                                                        */
    void add(const std::string& name, grade_t grade_level_param);

    /*  Return the list of students for the requested grade.
        The list is sorted alphabetically.                             */
    std::vector<std::string> grade(grade_t grade_level) const;

    /*  Return the complete, grade-ordered roster with students in
        each grade sorted alphabetically.                              */
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::set<std::string>> m_roster {};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
