#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;
using student_list_t = std::vector<std::string>;
using roster_t = std::map<grade_t, student_list_t>;

class school {
public:
    school() = default;

    /* Add a student to a grade; silently ignored if already present. */
    void add(const std::string& name, grade_t grade_level);

    /* Return the list of students in the requested grade. */
    student_list_t grade(grade_t grade_level) const;

    /* Return the full roster. */
    roster_t roster() const;

private:
    roster_t m_roster {};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
