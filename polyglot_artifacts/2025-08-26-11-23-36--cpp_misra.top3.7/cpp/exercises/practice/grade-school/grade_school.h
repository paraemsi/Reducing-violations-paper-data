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

class school {
public:
    // Add a student to a grade. Returns true if added, false if already present.
    bool add(const name_t& student, grade_t grade);

    // Get a sorted list of students in a grade.
    std::vector<name_t> grade(grade_t grade) const;

    // Get a sorted map of all grades to students (for test compatibility).
    std::map<int, std::vector<std::string>> grades() const;

    // Get a sorted roster of all students in all grades.
    std::vector<name_t> roster() const;

private:
    // Map from grade to set of student names (sorted).
    std::map<grade_t, std::set<name_t> > m_students;
    // Set of all student names for uniqueness.
    std::set<name_t> m_all_students;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
