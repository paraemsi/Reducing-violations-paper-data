#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdint>

namespace grade_school {

using grade_t = int;
using name_t = std::string;

class school {
public:
    // Add a student to a grade. Returns true if added, false if already present.
    bool add(const name_t& name, grade_t grade);

    // Get a sorted list of students in a grade.
    std::vector<name_t> grade(grade_t grade) const;

    // Get a sorted list of all students in all grades, sorted by grade then name.
    std::map<grade_t, std::vector<name_t> > roster() const;

private:
    // Map from grade to set of names (sorted).
    std::map<grade_t, std::set<name_t> > m_roster;
    // Set of all student names for uniqueness.
    std::set<name_t> m_all_students;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
