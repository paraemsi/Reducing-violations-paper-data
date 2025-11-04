#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school
{
public:
    using grade_type  = std::int32_t;
    using student_set   = std::set<std::string>;              // internal ― keeps names sorted
    using student_list  = std::vector<std::string>;           // external ― returned to callers
    using roster_output = std::map<grade_type, student_list>; // public roster type
    using roster_map    = std::map<grade_type, student_set>;  // internal storage

    // Add a student to a grade.
    // Returns true on success, false if the student already exists anywhere.
    bool add(const std::string& name, grade_type grade);

    // Return the complete roster, already sorted by grade then by name.
    roster_output roster() const;

    // Return a (possibly empty) list of students in the requested grade.
    student_list grade(grade_type grade) const;

private:
    roster_map m_roster;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
