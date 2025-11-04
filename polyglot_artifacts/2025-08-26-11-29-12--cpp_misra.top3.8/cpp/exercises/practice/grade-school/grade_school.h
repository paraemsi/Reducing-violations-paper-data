#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdint>

namespace grade_school {

using grade_t = int;

class school {
public:
    // Add a student to a grade. Returns true if added, false if already present.
    bool add(const std::string& name, grade_t grade);

    // Get a sorted list of students in a grade.
    std::vector<std::string> grade(grade_t) const;

    // Get a sorted roster: map of grade to vector of names.
    std::map<grade_t, std::vector<std::string> > roster() const;

private:
    // Map grade -> set of names (set keeps names sorted and unique)
    std::map<grade_t, std::set<std::string> > m_roster;
    // Map name -> grade (for uniqueness check)
    std::map<std::string, grade_t> m_student_grade;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
