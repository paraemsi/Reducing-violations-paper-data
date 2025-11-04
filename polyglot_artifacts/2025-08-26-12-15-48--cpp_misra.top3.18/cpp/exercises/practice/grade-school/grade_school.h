#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdint>

namespace grade_school {

typedef std::uint16_t grade_t;
typedef std::string student_t;

class school {
public:
    // Add a student to a grade. Returns true if added, false if already present.
    bool add(const student_t& name, grade_t grade);

    // Get a sorted list of students in a grade.
    std::vector<student_t> grade(grade_t grade) const;

    // Get a sorted roster of all students in all grades.
    std::map<int, std::vector<std::string> > roster() const;

private:
    // Map from grade to set of students (sorted by name).
    std::map<grade_t, std::set<student_t> > m_roster;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
