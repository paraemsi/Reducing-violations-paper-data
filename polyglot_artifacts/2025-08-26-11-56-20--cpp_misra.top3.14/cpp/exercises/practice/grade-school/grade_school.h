#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdint>

namespace grade_school {

using grade_t = std::uint16_t;
using student_t = std::string;

class school {
public:
    // Add a student to a grade. Returns true if added, false if already present.
    bool add(const student_t& name, grade_t grade);

    // Get a sorted list of students in a grade.
    std::vector<student_t> grade(grade_t grade) const;

    // Get a sorted roster: map of grade to vector of students.
    std::map<int, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::set<student_t>> m_roster;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
