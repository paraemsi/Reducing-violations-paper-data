#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdint>

namespace grade_school {

typedef std::uint16_t grade_t;

class school {
public:
    // Add a student to a grade. Returns true if added, false if already present.
    bool add(const std::string& name, grade_t grade);

    // Get a sorted list of students in a grade.
    std::vector<std::string> grade(grade_t grade) const;

    // Get a sorted roster: map of grade (int) to vector of names.
    std::map<int, std::vector<std::string> > roster() const;

private:
    // grade -> set of names (sorted, unique)
    std::map<grade_t, std::set<std::string> > m_roster;
    // name -> grade (for uniqueness)
    std::map<std::string, grade_t> m_name_to_grade;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
