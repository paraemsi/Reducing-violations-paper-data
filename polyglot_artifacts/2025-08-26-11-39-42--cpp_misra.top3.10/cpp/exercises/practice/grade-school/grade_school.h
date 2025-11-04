#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdint>

namespace grade_school {

typedef std::uint16_t grade_t;
typedef std::string name_t;

// For test compatibility, provide a public type alias for the roster map key type
using roster_grade_key_t = int;

class school {
public:
    // Add a student to a grade. Returns true if added, false if already present.
    bool add(const name_t& student, grade_t grade);

    // Get a sorted list of students in a grade.
    std::vector<name_t> grade(grade_t grade) const;

    // Get a sorted roster of all students in all grades.
    std::map<roster_grade_key_t, std::vector<name_t> > roster() const;

private:
    // Map grade to set of student names (set for uniqueness and sorting)
    std::map<grade_t, std::set<name_t> > m_roster;
    // Map student name to grade for uniqueness check
    std::map<name_t, grade_t> m_student_grade;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
