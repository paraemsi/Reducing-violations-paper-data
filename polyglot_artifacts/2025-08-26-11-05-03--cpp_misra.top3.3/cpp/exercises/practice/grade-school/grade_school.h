#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdint>

namespace grade_school {

using student_name = std::string;
using grade_t = std::uint32_t;

class school {
public:
    // Add a student to a grade. Returns true if added, false if already present.
    bool add(const student_name& name, grade_t grade);

    // Get a sorted list of students in a grade.
    std::vector<student_name> grade(grade_t grade) const;

    // Get a sorted roster of all students in all grades.
    std::map<grade_t, std::vector<student_name> > roster() const;

private:
    // Map from grade to set of student names (sorted).
    std::map<grade_t, std::set<student_name>> m_grades;
    // Set of all student names for uniqueness.
    std::set<student_name> m_all_students;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
